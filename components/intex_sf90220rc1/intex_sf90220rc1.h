#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include <array>
#include <cstdint>
#include <vector>

namespace esphome {
namespace switch_ {
class Switch;
}

namespace intex_sf90220rc1 {

class IntexSF90220RC1 : public Component, public uart::UARTDevice {
  public:

    void setup() override;
    void loop() override;
    void dump_config() override;

    void set_power_switch(switch_::Switch *power_switch) { this->power_switch_ = power_switch; }

  protected:
    void process_rx();
    void process_msg();

    uint32_t last_write_{0};

    // discard at boot until frame timeout (might have woken up in the middle of a frame)
    bool receiving_{false};
    uint32_t last_rx_byte_time_{0};
    uint32_t last_rx_msg_time_{0};
    std::vector<uint8_t> rx_msg_;

    switch_::Switch *power_switch_{nullptr};
};

} //namespace intex_sf90220rc1
} //namespace esphome
