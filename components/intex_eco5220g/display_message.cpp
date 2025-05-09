#include "display_message.h"

namespace esphome {
namespace intex_eco5220g {

DisplayMessage::DisplayMessage(const RawMessage& raw_message) : raw_message_(raw_message) {}

bool DisplayMessage::is_power_on_set() const {
  return (this->raw_message_[kLedByteOffset] & LedBit::kPowerOn) == LedBit::kPowerOn;
}

}  // namespace intex_eco5220g
}  // namespace esphome
