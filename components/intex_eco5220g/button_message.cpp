#include "button_message.h"

namespace esphome {
namespace intex_eco5220g {

ButtonMessage::ButtonMessage(const RawMessage& raw_message) : raw_message_(raw_message) {}

void ButtonMessage::set_button(Button button) {
  this->raw_message_[kButtonByteOffset] |= static_cast<uint8_t>(button);
  this->update_inversion();
}

void ButtonMessage::update_inversion() {
  this->raw_message_[kInvertedButtonByteOffset] = ~this->raw_message_[kButtonByteOffset];
}

const ButtonMessage::RawMessage& ButtonMessage::raw_message() const { return this->raw_message_; }

}  // namespace intex_eco5220g
}  // namespace esphome
