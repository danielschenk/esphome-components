#pragma once
#include <array>
#include <cstdint>

namespace intex_eco5220g {

typedef std::array<uint8_t, 4> RawMessage;

class DisplayMessage
{
  public:
    DisplayMessage() = default;
    DisplayMessage(const DisplayMessage& other) = default;
    DisplayMessage& operator=(const DisplayMessage& other) = default;

    DisplayMessage(const RawMessage& raw_message);

  protected:
    RawMessage raw_message_{0};
};

} //namespace intex_eco5220g
