#include "../display_message.h"

#include <gtest/gtest.h>

namespace esphome {
namespace intex_eco5220g {

TEST(DisplayMessageTest, IsPowerOnSet) {
  DisplayMessage message;
  EXPECT_FALSE(message.is_power_on_set());
  DisplayMessage message2({0, 0, 0x02, 0});
  EXPECT_TRUE(message2.is_power_on_set());
}

}  // namespace intex_eco5220g
}  // namespace esphome
