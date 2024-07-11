#pragma once

namespace esphome {
namespace intex_common {

class Timer {
  public:
    enum TimerSetting {
      INFINITE = -1,
    };

    virtual TimerSetting timer_setting() const = 0;
    virtual void increment_timer_setting() = 0;
};

}
}
