#pragma once

namespace esphome {
namespace switch_ {

class Switch {
  public:
    virtual ~Switch() = default;

    virtual void publish_state(bool state) = 0;
};

}  // namespace switch_
}  // namespace esphome
