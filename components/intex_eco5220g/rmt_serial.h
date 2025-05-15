#pragma once

#include "esphome/components/intex_common/serial.h"
#include "esphome/core/component.h"

namespace esphome {
namespace intex_eco5220g {

class RmtSerial : public Component, public intex_common::Serial {
  public:
    RmtSerial() = default;

    void setup() override;

    void send(const uint8_t *data, size_t length) override;
};

}  // namespace intex_eco5220g
}  // namespace esphome
