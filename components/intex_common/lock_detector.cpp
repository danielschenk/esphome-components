#include "lock_detector.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"

namespace esphome {
namespace intex_common {

static constexpr const char *TAG = "intex_common";

void LockDetector::update(bool is_screen_blank, bool is_power_on) {
  uint32_t now = millis();
  if (is_screen_blank) {
    this->is_locked_ = false;
    this->last_blank_time_ = now;
  } else if (!is_power_on || now - this->last_blank_time_ > this->kBlinkTimeoutMillis) {
    this->is_locked_ = true;
  }

  if (this->is_locked_.has_value()) {
    if (this->dedup_is_locked_.next(*this->is_locked_)) {
      ESP_LOGI(TAG, "Settings %slocked", *this->is_locked_ ? "" : "un");
    }
  }
}

}
}
