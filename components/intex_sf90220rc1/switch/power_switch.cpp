#include "power_switch.h"
#include "esphome/core/log.h"
#include "esphome/core/application.h"

namespace esphome {
namespace intex_sf90220rc1 {

static const char *const TAG = "intexsf90220rc1.switch";

void PowerSwitch::dump_config() { LOG_SWITCH("", "Power Switch", this); }
void PowerSwitch::write_state(bool state) {
  // TODO
}

}  // namespace intexsf90220rc1
}  // namespace esphome
