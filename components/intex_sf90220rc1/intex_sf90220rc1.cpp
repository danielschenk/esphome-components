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
  static constexpr size_t kDisplayByteOffset = 2;
  enum DisplayValue : uint8_t {
    kBlank = 0xBB,
    kDot = 0xAB,
  };

  static constexpr uint32_t kBaudRate = 2400;
  static constexpr uint32_t kCharacterBits = 10; // 8N1: 8 data bits, no parity, 1 start and 1 stop bit
  static constexpr uint32_t kCharacterTimeoutMillis = 1000 * (1.5 * kCharacterBits / kBaudRate);
} //namespace messages

static const char *TAG = "intex_sf90220rc1";

void IntexSF90220RC1::setup() {

}

void IntexSF90220RC1::loop() {
  uint32_t now = millis();
  if (now - this->last_write_ > 2000) {
    this->write_array(messages::kPowerPressed);
    this->last_write_ = now;
  }

  process_rx();
}

void IntexSF90220RC1::process_rx() {
  uint32_t now = millis();

  while (this->available()) {
    uint8_t byte;
    this->read_byte(&byte);
    if (this->receiving_) {
      this->rx_msg_.push_back(byte);
    }
    this->last_rx_byte_time_ = now;
  }

  if (now - this->last_rx_byte_time_ >= messages::kCharacterTimeoutMillis) {
    this->receiving_ = true;
  } else {
    return;
  }

  if (this->rx_msg_.empty()) {
    return;
  }

  process_msg();
}

void IntexSF90220RC1::process_msg() {
  if (this->rx_msg_.size() < messages::kMinReceiveSize) {
    ESP_LOGD(TAG, "Received invalid frame: insufficient size");
    this->rx_msg_.clear();
    return;
  }

  if (this->rx_msg_[0] != messages::kDisplayHeader[0] ||
      this->rx_msg_[1] != messages::kDisplayHeader[1]) {
    ESP_LOGD(TAG, "Received invalid frame: unexpected header");
    this->rx_msg_.clear();
    return;
  }

  uint8_t displayByte = this->rx_msg_[messages::kDisplayByteOffset];
  this->power_switch_->publish_state(displayByte != messages::DisplayValue::kDot);

  this->rx_msg_.clear();
}

void IntexSF90220RC1::dump_config() {
    ESP_LOGCONFIG(TAG, "Intex SF90220RC1 filter pump");
}

} //namespace intex_sf90220rc1
} //namespace esphome
