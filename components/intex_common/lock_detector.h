#pragma once

#include <cstdint>

#include "esphome/core/optional.h"

namespace esphome {
namespace intex_common {

class MonotonicClock;

class LockDetector {
  public:
    explicit LockDetector(const MonotonicClock &clock);

    void update(bool is_screen_blank, bool is_power_on);
    optional<bool> is_locked() const { return this->is_locked_; }

  protected:
    const MonotonicClock &clock_;

    optional<bool> is_locked_;
    optional<bool> prev_is_locked_;
    static constexpr uint32_t kBlinkTimeoutMillis = 1500;
    uint32_t last_blank_time_{0};
};

}  // namespace intex_common
}  // namespace esphome
