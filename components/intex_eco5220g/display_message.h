#pragma once
#include <array>
#include <cstdint>

namespace esphome {
namespace intex_eco5220g {

class DisplayMessage {
  public:
    typedef std::array<uint8_t, 4> RawMessage;
    DisplayMessage() = default;
    DisplayMessage(const DisplayMessage& other) = default;
    DisplayMessage& operator=(const DisplayMessage& other) = default;

    DisplayMessage(const RawMessage& raw_message);

    bool is_power_on_set() const;

  protected:
    static constexpr size_t kLedByteOffset = 2;
    enum LedBit : uint8_t
    {
      kPowerOn = 0x02,
    };

    RawMessage raw_message_{0};
};

} //namespace intex_eco5220g
} //namespace esphome
