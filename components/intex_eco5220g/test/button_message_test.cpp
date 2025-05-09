#include "../button_message.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::ElementsAreArray;

namespace esphome {
namespace intex_eco5220g {

TEST(ButtonMessageTest, CreateNoButtonsSet) {
  ButtonMessage message;
  EXPECT_THAT(message.raw_message(), ElementsAreArray({0xFF, 0x00}));
}

TEST(ButtonMessageTest, SetSelfClean) {
  ButtonMessage message;
  message.set_button(ButtonMessage::Button::kSelfClean);
  EXPECT_THAT(message.raw_message(), ElementsAreArray({0xEF, 0x10}));
}

TEST(ButtonMessageTest, SetTogglePower) {
  ButtonMessage message;
  message.set_button(ButtonMessage::Button::kTogglePower);
  EXPECT_THAT(message.raw_message(), ElementsAreArray({0xDF, 0x20}));
}

TEST(ButtonMessageTest, SetToggleLock) {
  ButtonMessage message;
  message.set_button(ButtonMessage::Button::kToggleLock);
  EXPECT_THAT(message.raw_message(), ElementsAreArray({0x7F, 0x80}));
}

TEST(ButtonMessageTest, SetMultiple) {
  ButtonMessage message;
  message.set_button(ButtonMessage::Button::kTogglePower);
  message.set_button(ButtonMessage::Button::kSelfClean);
  EXPECT_THAT(message.raw_message(), ElementsAreArray({0xCF, 0x30}));
}

}  // namespace intex_eco5220g
}  // namespace esphome
