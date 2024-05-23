#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include <array>
#include <cstdint>
#include <deque>

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
    bool read_display_msg(uint8_t& display_byte);

    void update_power_state(bool state, const char* source);

    uint32_t last_write_{0};

    // discard at boot until frame timeout (might have woken up in the middle of a frame)
    bool receiving_{false};
    uint32_t last_rx_byte_time_{0};
    uint32_t last_rx_msg_time_{0};
    std::deque<uint8_t> rx_buf_;

    // due to lack of std::optional support, track this in a separate var
    bool power_state_known_{false};
    bool last_power_state_;
    switch_::Switch *power_switch_{nullptr};
};

} //namespace intex_sf90220rc1
} //namespace esphome
