#include "intex_eco5220g.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"
#include "esphome/components/switch/switch.h"

namespace esphome {
namespace intex_eco5220g {

static const char *TAG = "intex_eco5220g";

void IntexECO5220G::setup() {
}

void IntexECO5220G::loop() {
}

optional<bool> IntexECO5220G::is_power_on() const {
  return this->last_power_state_;
}

void IntexECO5220G::press_power() {
  this->try_tx(messages::kPowerPressed, "power");
}

optional<bool> IntexECO5220G::is_locked() const {
  return this->lock_detector_.is_locked();
}

void IntexECO5220G::press_toggle_lock() {
}

intex_common::CommonHmi::TimerSetting IntexECO5220G::timer_setting() const {
  if (!this->timer_setting_.has_value()) {
    return TimerSetting::UNKNOWN;
  }
  return *this->timer_setting_;
}

void IntexECO5220G::press_increment_timer_setting() {
}

void IntexECO5220G::dump_config() {
  ESP_LOGCONFIG(TAG, "Intex ECO5220G filter pump");
}

} //namespace intex_eco5220g
} //namespace esphome
