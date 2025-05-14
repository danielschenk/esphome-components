#pragma once

#include <array>
#include <cstdint>
#include <deque>

#include "esphome/components/intex_common/common_hmi.h"
#include "esphome/components/intex_common/lock_detector.h"
#include "esphome/components/intex_common/timer_immobilizer.h"
#include "esphome/core/component.h"
#include "esphome/core/optional.h"

namespace esphome {
namespace switch_ {
class Switch;
}

namespace intex_common {
class MonotonicClock;
}

namespace intex_eco5220g {

class IntexECO5220G : public Component, public intex_common::CommonHmi {
  public:
    explicit IntexECO5220G(intex_common::MonotonicClock &clock);

    void setup() override;
    void loop() override;
    void dump_config() override;

    void set_power_switch(switch_::Switch *power_switch) { this->power_switch_ = power_switch; }

    optional<bool> is_power_on() const override;
    void press_power() override;

    optional<bool> is_locked() const override;
    void press_toggle_lock() override;

    TimerSetting timer_setting() const override;
    void press_increment_timer_setting() override;

  protected:
    intex_common::MonotonicClock &clock_;
    intex_common::LockDetector lock_detector_{clock_};
    intex_common::TimerImmobilizer timer_immobilizer_{*this, clock_};

    optional<bool> last_power_state_;
    optional<TimerSetting> timer_setting_;

    switch_::Switch *power_switch_{nullptr};
};

}  // namespace intex_eco5220g
}  // namespace esphome
