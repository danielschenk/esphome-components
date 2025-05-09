#include "power_switch.h"
#include "../intex_eco5220g.h"
#include "esphome/core/log.h"
#include "esphome/core/application.h"

namespace esphome {
namespace intex_eco5220g {

static const char *const TAG = "intexsf90220rc1.switch";

void PowerSwitch::dump_config() { LOG_SWITCH("", "Power Switch", this); }

void PowerSwitch::write_state(bool state) {
}

}  // namespace intex_eco5220g
}  // namespace esphome
