#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include <array>
#include <cstdint>

namespace esphome {
namespace intex_sf90220rc1 {

class IntexSF90220RC1 : public Component, public uart::UARTDevice {
  public:

    void setup() override;
    void loop() override;
    void dump_config() override;

  protected:
    uint32_t last_write_{0};

    static constexpr std::array<uint8_t, 4> kPowerPressed{0x02, 0xFD, 0x04, 0x00};
};

} //namespace intex_sf90220rc1
} //namespace esphome
