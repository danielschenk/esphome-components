#pragma once

#include <cstdio>

namespace esphome {

class Component {
  public:
    virtual ~Component() = default;
    virtual void setup() {}
    virtual void loop() {}
    virtual void dump_config() {}

    static constexpr uint32_t COMPONENT_STATE_FAILED = 0x03;

    void mark_failed() { component_state_ |= COMPONENT_STATE_FAILED; }
    uint32_t get_component_state() const { return component_state_; }

  private:
    uint32_t component_state_{0};
};

}  // namespace esphome
