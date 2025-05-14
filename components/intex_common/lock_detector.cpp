#include "lock_detector.h"

#include "esphome/core/log.h"
#include "monotonic_clock.h"

namespace esphome {
namespace intex_common {

static constexpr const char *TAG = "intex_common";

LockDetector::LockDetector(const MonotonicClock &clock) : clock_(clock) {}

void LockDetector::update(bool is_screen_blank, bool is_power_on) {
  uint32_t now = clock_.millis();
  if (!is_power_on) {
    this->is_locked_ = true;
  } else if (is_screen_blank) {
    this->is_locked_ = false;
    this->last_blank_time_ = now;
  } else if (now - this->last_blank_time_ > this->kBlinkTimeoutMillis) {
    this->is_locked_ = true;
  }

  if (this->is_locked_.has_value()) {
    if (this->prev_is_locked_.has_value()) {
      if (*this->prev_is_locked_ == *this->is_locked_) {
        return;
      }
      ESP_LOGI(TAG, "Settings %slocked", *this->is_locked_ ? "" : "un");
      this->prev_is_locked_ = this->is_locked_;
    }
  }
}

}  // namespace intex_common
}  // namespace esphome
