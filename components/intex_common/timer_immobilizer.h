#pragma once
#include <cstdint>

namespace esphome {
namespace intex_common {

class CommonHmi;
class MonotonicClock;

// Component which makes sure the timer is always set to infinite
class TimerImmobilizer {
  public:
    TimerImmobilizer(CommonHmi& hmi, MonotonicClock& clock);

    void update();

  private:
    CommonHmi& hmi_;
    MonotonicClock& clock_;
    uint32_t last_button_press_{0};
    static constexpr uint32_t kButtonPressIntervalMillis = 500;
};

}  // namespace intex_common
}  // namespace esphome
