#include "esphome/core/log.h"
#include "esphome/core/time.h"
#include "intex_sf90220rc1.h"

namespace esphome {
namespace intex_sf90220rc1 {

namespace messages {
  static constexpr std::array<uint8_t, 4> kPowerPressed{0x02, 0xFD, 0x04, 0x00};
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
}

void IntexSF90220RC1::dump_config() {
    ESP_LOGCONFIG(TAG, "Empty compound sensor");
}

} //namespace intex_sf90220rc1
} //namespace esphome
