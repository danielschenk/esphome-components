#pragma once

#include <cstdint>

#include "esphome/core/helpers.h"
#include "esphome/core/optional.h"

namespace esphome {
namespace intex_common {

class LockDetector {
  public:
    LockDetector() = default;

    void update(bool is_screen_blank, bool is_power_on);
    optional<bool> is_locked() const { return this->is_locked_; }

  protected:
    optional<bool> is_locked_;
    Deduplicator<bool> dedup_is_locked_;
    static constexpr uint32_t kBlinkTimeoutMillis = 1500;
    uint32_t last_blank_time_{0};
};

}  // namespace intex_common
}  // namespace esphome
