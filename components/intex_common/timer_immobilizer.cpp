#include "timer_immobilizer.h"

#include "common_hmi.h"
#include "monotonic_clock.h"

namespace esphome {
namespace intex_common {

TimerImmobilizer::TimerImmobilizer(CommonHmi& hmi, MonotonicClock& clock)
    : hmi_(hmi), clock_(clock) {}

void TimerImmobilizer::update() {
  auto is_power_on = this->hmi_.is_power_on();
  auto is_locked = this->hmi_.is_locked();
  CommonHmi::TimerSetting timer_setting = this->hmi_.timer_setting();
  if (!is_power_on.has_value() || !is_locked.has_value() ||
      timer_setting == CommonHmi::TimerSetting::UNKNOWN) {
    // do nothing when we don't know all state
    return;
  }

  if (!*is_power_on) {
    return;
  }

  uint32_t now = clock_.millis();
  if (timer_setting != CommonHmi::TimerSetting::INFINITE &&
      now - this->last_button_press_ >= this->kButtonPressIntervalMillis) {
    // try changing timer to infinite
    if (*is_locked) {
      this->hmi_.press_toggle_lock();
    } else {
      this->hmi_.press_increment_timer_setting();
    }
    this->last_button_press_ = now;
  }
}

}  // namespace intex_common
}  // namespace esphome
