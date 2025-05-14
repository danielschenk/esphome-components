#pragma once
#include <cstdint>

namespace esphome {
namespace intex_common {

// Interface for monotonic clocks
class MonotonicClock {
  public:
    virtual ~MonotonicClock() = default;

    // Returns the current time in milliseconds since boot
    virtual uint32_t millis() const = 0;
};

}  // namespace intex_common
}  // namespace esphome
