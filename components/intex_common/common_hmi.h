#pragma once
#include "esphome/core/optional.h"

namespace esphome {
namespace intex_common {

// Interface for common HMI functionality
class CommonHmi {
  public:
    virtual ~CommonHmi() = default;

    virtual void press_power() = 0;
    virtual optional<bool> is_power_on() const = 0;

    virtual void press_toggle_lock() = 0;
    virtual optional<bool> is_locked() const = 0;

    enum TimerSetting {
      UNKNOWN = -2,
      INFINITE = -1,
    };

    virtual TimerSetting timer_setting() const = 0;
    virtual void press_increment_timer_setting() = 0;
};

}
}
