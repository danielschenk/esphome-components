#include "intex_sf90220rc1.h"

#include "esphome/components/switch/switch.h"
#include "esphome/core/hal.h"
#include "esphome/core/log.h"

namespace esphome {
namespace intex_sf90220rc1 {

namespace messages {
static constexpr std::array<uint8_t, 4> kPowerPressed{0x02, 0xFD, 0x04, 0x00};
static constexpr std::array<uint8_t, 4> kTimePressed{0x02, 0xFD, 0x02, 0x00};
static constexpr std::array<uint8_t, 4> kLockUnlockPressed{0x02, 0xFD, 0x01, 0x00};

static constexpr std::array<uint8_t, 2> kDisplayHeader{0x00, 0xFF};
static constexpr size_t kMinReceiveSize = 4;
enum DisplayValue : uint8_t {
  kBlank = 0xBB,
  kDot = 0xAB,
  kTimerDisabled = 0xFE,
};

static constexpr uint32_t kBaudRate = 2400;
static constexpr uint32_t kCharacterBits =
    10;  // 8N1: 8 data bits, no parity, 1 start and 1 stop bit
static constexpr uint32_t kCharacterTimeoutMillis = 1000 * (1.5 * kCharacterBits / kBaudRate);

static constexpr uint32_t kDisplayMessageTimeoutMillis = 1000;
}  // namespace messages

static const char* TAG = "intex_sf90220rc1";

void IntexSF90220RC1::setup() {}

void IntexSF90220RC1::loop() {
  process_rx();
  this->timer_immobilizer_.update();
}

optional<bool> IntexSF90220RC1::is_power_on() const { return this->last_power_state_; }

void IntexSF90220RC1::press_power() { this->try_tx(messages::kPowerPressed, "power"); }

optional<bool> IntexSF90220RC1::is_locked() const { return this->lock_detector_.is_locked(); }

void IntexSF90220RC1::press_toggle_lock() {
  this->try_tx(messages::kLockUnlockPressed, "lock/unlock");
}

intex_common::CommonHmi::TimerSetting IntexSF90220RC1::timer_setting() const {
  if (!this->timer_setting_.has_value()) {
    return TimerSetting::UNKNOWN;
  }
  return *this->timer_setting_;
}

void IntexSF90220RC1::press_increment_timer_setting() {
  this->try_tx(messages::kTimePressed, "time");
}

void IntexSF90220RC1::process_rx() {
  uint32_t now = millis();
  if (now - this->last_rx_msg_time_ >= messages::kDisplayMessageTimeoutMillis) {
    update_power_state(false, "display message timeout");
  }

  while (this->available()) {
    uint8_t byte;
    this->read_byte(&byte);
    if (this->receiving_) {
      this->rx_buf_.push_back(byte);
    }
    this->last_rx_byte_time_ = now;
  }

  if (now - this->last_rx_byte_time_ >= messages::kCharacterTimeoutMillis) {
    this->receiving_ = true;
  } else {
    return;
  }

  if (this->rx_buf_.empty()) {
    return;
  }

  this->process_msg();
}

void IntexSF90220RC1::process_msg() {
  size_t bytes_avail = this->rx_buf_.size();
  if (bytes_avail < messages::kMinReceiveSize) {
    ESP_LOGD(TAG, "Received invalid frame: insufficient size");
    this->rx_buf_.clear();
    return;
  }

  size_t num_msgs = bytes_avail / messages::kMinReceiveSize;
  for (size_t msg = 0; msg < num_msgs; ++msg) {
    uint8_t display_byte;
    if (!this->read_display_msg(display_byte)) {
      continue;
    }
    bool power_on = display_byte != messages::DisplayValue::kDot;
    update_power_state(power_on, "display message");
    update_lock_state(display_byte, power_on);
    if (power_on && (display_byte != messages::DisplayValue::kBlank)) {
      update_timer_state(display_byte);
    }
  }

  this->last_rx_msg_time_ = millis();
}

bool IntexSF90220RC1::read_display_msg(uint8_t& display_byte) {
  uint8_t header1, header2;
  header1 = this->rx_buf_.front();
  this->rx_buf_.pop_front();
  header2 = this->rx_buf_.front();
  this->rx_buf_.pop_front();

  if (header1 != messages::kDisplayHeader[0] || header2 != messages::kDisplayHeader[1]) {
    ESP_LOGD(TAG, "Received invalid frame: unexpected header");
    this->rx_buf_.pop_front();
    this->rx_buf_.pop_front();
    return false;
  }

  display_byte = this->rx_buf_.front();
  this->rx_buf_.pop_front();
  this->rx_buf_.pop_front();
  return true;
}

void IntexSF90220RC1::update_power_state(bool state, const char* source) {
  if (this->last_power_state_.has_value()) {
    if (*this->last_power_state_ == state) {
      return;
    }
  }

  if (this->power_switch_ != nullptr) {
    this->power_switch_->publish_state(state);
  }
  ESP_LOGI(TAG, "Turned %s (detected by %s)", state ? "on" : "off", source);
  this->last_power_state_ = state;
}

void IntexSF90220RC1::update_timer_state(uint8_t display_byte) {
  TimerSetting setting;
  if (display_byte == messages::DisplayValue::kTimerDisabled) {
    setting = TimerSetting::INFINITE;
  } else if (display_byte >= 0x00 && display_byte <= 0x12) {
    // a kind of BCD: the high nibble contains the tens, the low nibble the ones
    setting = static_cast<TimerSetting>((display_byte & 0xF) + 10 * (display_byte >> 4));
  } else {
    ESP_LOGE(TAG, "Received unexpected display value: %#02x", display_byte);
    return;
  }

  if (this->timer_setting_.has_value()) {
    if (*this->timer_setting_ == setting) {
      return;
    }
  }
  if (setting == TimerSetting::INFINITE) {
    ESP_LOGI(TAG, "Timer disabled");
  } else {
    ESP_LOGI(TAG, "Timer ending in %d hours", static_cast<int>(setting));
  }
  this->timer_setting_ = setting;
}

void IntexSF90220RC1::update_lock_state(uint8_t display_byte, bool power_on) {
  this->lock_detector_.update(display_byte == messages::DisplayValue::kBlank, power_on);
}

bool IntexSF90220RC1::try_tx(std::array<uint8_t, 4> message, const char* log_description) {
  uint32_t now = millis();
  if (now - this->last_tx_ < this->kTxIntervalMillis) {
    return false;
  }
  this->write_array(message);
  this->last_tx_ = now;
  if (log_description) {
    ESP_LOGD(TAG, "Transmitted message: %s", log_description);
  }
  return true;
}

void IntexSF90220RC1::dump_config() { ESP_LOGCONFIG(TAG, "Intex SF90220RC1 filter pump"); }

}  // namespace intex_sf90220rc1
}  // namespace esphome
