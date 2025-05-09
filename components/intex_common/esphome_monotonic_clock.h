#pragma once

#include "monotonic_clock.h"

namespace esphome {
namespace intex_common {

// Implementation of the MonotonicClock interface for ESPHome
class EspHomeMonotonicClock : public MonotonicClock {
  public:
    EspHomeMonotonicClock() = default;
    // Returns the current time in milliseconds since boot
    uint32_t millis() const override;
};

}  // namespace intex_common
}  // namespace esphome
