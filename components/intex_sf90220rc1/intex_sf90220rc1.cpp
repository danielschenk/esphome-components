#include "intex_sf90220rc1.h"
#include "esphome/core/log.h"
#include "esphome/core/time.h"
#include "esphome/components/switch/switch.h"

namespace esphome {
namespace intex_sf90220rc1 {

namespace messages {
  static constexpr std::array<uint8_t, 4> kPowerPressed{0x02, 0xFD, 0x04, 0x00};

  static constexpr std::array<uint8_t, 2> kDisplayHeader{0x00, 0xFF};
  static constexpr size_t kMinReceiveSize = 4;
  enum DisplayValue : uint8_t {
    kBlank = 0xBB,
    kDot = 0xAB,
  };

  static constexpr uint32_t kBaudRate = 2400;
  static constexpr uint32_t kCharacterBits = 10; // 8N1: 8 data bits, no parity, 1 start and 1 stop bit
  static constexpr uint32_t kCharacterTimeoutMillis = 1000 * (1.5 * kCharacterBits / kBaudRate);

  static constexpr uint32_t kDisplayMessageTimeoutMillis = 1000;
} //namespace messages

static const char *TAG = "intex_sf90220rc1";

void IntexSF90220RC1::setup() {

}

void IntexSF90220RC1::loop() {
  uint32_t now = millis();
  // for now, auto-toggle as a test
  if (now - this->last_write_ > 2000) {
    this->write_array(messages::kPowerPressed);
    this->last_write_ = now;
  }

  process_rx();
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

  process_msg();
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
    update_power_state(display_byte != messages::DisplayValue::kDot, "display message");
  }

  this->last_rx_msg_time_ = millis();
}

bool IntexSF90220RC1::read_display_msg(uint8_t& display_byte) {
  uint8_t header1, header2;
  header1 = this->rx_buf_.front();
  this->rx_buf_.pop_front();
  header2 = this->rx_buf_.front();
  this->rx_buf_.pop_front();

  if (header1 != messages::kDisplayHeader[0] ||
      header2 != messages::kDisplayHeader[1]) {
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
  if (!this->power_state_known_ || this->last_power_state_ != state) {
    this->power_switch_->publish_state(state);
    ESP_LOGI(TAG, "Turned %s (%s)", state ? "on" : "off", source);
    this->last_power_state_ = state;
    this->power_state_known_ = true;
  }
}

void IntexSF90220RC1::dump_config() {
    ESP_LOGCONFIG(TAG, "Intex SF90220RC1 filter pump");
}

} //namespace intex_sf90220rc1
} //namespace esphome
