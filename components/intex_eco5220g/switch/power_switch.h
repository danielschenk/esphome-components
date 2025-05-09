#pragma once

#include "esphome/components/switch/switch.h"
#include "esphome/core/component.h"

namespace esphome {
namespace intex_eco5220g {
class IntexECO5220G;
class PowerSwitch : public switch_::Switch, public Component {
  public:
    void set_parent(IntexECO5220G *parent) { this->parent_ = parent; };
    void dump_config() override;

  protected:
    void write_state(bool state) override;
    IntexECO5220G *parent_;
};

}  // namespace intex_eco5220g
}  // namespace esphome
