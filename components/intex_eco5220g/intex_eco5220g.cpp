#include "intex_eco5220g.h"

#include "button_message.h"
#include "esphome/components/intex_common/serial.h"
#include "esphome/components/switch/switch.h"
#include "esphome/core/log.h"

namespace esphome {
namespace intex_eco5220g {

static const char *TAG = "intex_eco5220g";

IntexECO5220G::IntexECO5220G(intex_common::MonotonicClock &clock, intex_common::Serial &serial)
    : clock_(clock), serial_(serial) {}

void IntexECO5220G::setup() {}

void IntexECO5220G::loop() {}

optional<bool> IntexECO5220G::is_power_on() const {
  return this->last_power_state_;
}

void IntexECO5220G::press_power() {
  ButtonMessage message;
  message.set_button(ButtonMessage::Button::kTogglePower);
  this->serial_.send(message.raw_message());
}

optional<bool> IntexECO5220G::is_locked() const {
  return this->lock_detector_.is_locked();
}

void IntexECO5220G::press_toggle_lock() {
  ButtonMessage message;
  message.set_button(ButtonMessage::Button::kToggleLock);
  this->serial_.send(message.raw_message());
}

intex_common::CommonHmi::TimerSetting IntexECO5220G::timer_setting() const {
  if (!this->timer_setting_.has_value()) {
    return TimerSetting::UNKNOWN;
  }
  return *this->timer_setting_;
}

void IntexECO5220G::press_increment_timer_setting() {}

void IntexECO5220G::dump_config() {
  ESP_LOGCONFIG(TAG, "Intex ECO5220G saltwater chlorinator");
}

}  // namespace intex_eco5220g
}  // namespace esphome
