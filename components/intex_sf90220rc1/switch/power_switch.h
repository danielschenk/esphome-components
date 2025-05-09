#pragma once

#include "esphome/components/switch/switch.h"
#include "esphome/core/component.h"

namespace esphome {
namespace intex_sf90220rc1 {
class IntexSF90220RC1;
class PowerSwitch : public switch_::Switch, public Component {
  public:
    void set_parent(IntexSF90220RC1 *parent) { this->parent_ = parent; };
    void dump_config() override;

  protected:
    void write_state(bool state) override;
    IntexSF90220RC1 *parent_;
};

}  // namespace intex_sf90220rc1
}  // namespace esphome
