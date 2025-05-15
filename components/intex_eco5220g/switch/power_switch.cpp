#include "power_switch.h"

#include "../intex_eco5220g.h"
#include "esphome/core/application.h"
#include "esphome/core/log.h"

namespace esphome {
namespace intex_eco5220g {

static const char *const TAG = "intexeco5220g.switch";

void PowerSwitch::dump_config() {
  LOG_SWITCH("", "Power Switch", this);
}

void PowerSwitch::write_state(bool state) {
  if (this->parent_ == nullptr) {
    ESP_LOGE(TAG, "Parent is null");
    return;
  }

  auto is_power_on = this->parent_->is_power_on();
  if (!is_power_on.has_value()) {
    ESP_LOGE(TAG, "Power state is unknown, cannot toggle");
    return;
  }

  if (*is_power_on != state) {
    this->parent_->press_power();
  } else {
    ESP_LOGW(TAG, "Power state is already %s", state ? "on" : "off");
  }
}

}  // namespace intex_eco5220g
}  // namespace esphome
