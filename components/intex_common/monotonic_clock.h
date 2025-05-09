#pragma once
#include <cstdint>

// Interface for monotonic clocks
class MonotonicClock {
  public:
    virtual ~MonotonicClock() = default;

    // Returns the current time in milliseconds since boot
    virtual uint32_t millis() const = 0;
};
