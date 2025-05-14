#pragma once
#include <gmock/gmock.h>

#include "../monotonic_clock.h"

namespace esphome {
namespace intex_common {

class MockMonotonicClock : public MonotonicClock {
  public:
    MOCK_METHOD(uint32_t, millis, (), (const, override));
};

}  // namespace intex_common
}  // namespace esphome
