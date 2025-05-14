#include "../intex_eco5220g.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../button_message.h"
#include "esphome/components/intex_common/mock/mock_monotonic_clock.h"
#include "esphome/components/intex_common/mock/mock_serial.h"

namespace esphome {
namespace intex_eco5220g {

MATCHER_P2(CElementsAreArray, expected, size, "") {
  return memcmp(arg, expected, size * sizeof(expected[0])) == 0;
}

class IntexECO5220GTest : public ::testing::Test {
  protected:
    intex_common::MockMonotonicClock clock_;
    intex_common::MockSerial serial_;
    IntexECO5220G intex_eco5220g_{clock_, serial_};
};

TEST_F(IntexECO5220GTest, PressPowerButton) {
  ButtonMessage message;
  message.set_button(ButtonMessage::Button::kTogglePower);
  auto raw = message.raw_message();
  EXPECT_CALL(serial_, send(CElementsAreArray(raw.data(), raw.size()), raw.size()));
  intex_eco5220g_.press_power();
}

}  // namespace intex_eco5220g
}  // namespace esphome
