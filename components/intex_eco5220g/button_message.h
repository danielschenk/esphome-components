#pragma once
#include <array>
#include <cstddef>
#include <cstdint>

namespace esphome {
namespace intex_eco5220g {

class ButtonMessage {
  public:
    typedef std::array<uint8_t, 2> RawMessage;
    ButtonMessage() = default;
    ButtonMessage(const ButtonMessage& other) = default;
    ButtonMessage& operator=(const ButtonMessage& other) = default;

    ButtonMessage(const RawMessage& raw_message);

    enum class Button : uint8_t {
      kSelfClean = 0x10,
      kTogglePower = 0x20,
      kToggleLock = 0x80,
    };

    void set_button(Button button);

    const RawMessage& raw_message() const;

  protected:
    static constexpr size_t kInvertedButtonByteOffset = 0;
    static constexpr size_t kButtonByteOffset = 1;

    void update_inversion();

    RawMessage raw_message_{0xFF, 0x00};
};

}  // namespace intex_eco5220g
}  // namespace esphome
