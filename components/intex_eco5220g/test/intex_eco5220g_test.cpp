#include "../intex_eco5220g.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../button_message.h"
#include "esphome/components/intex_common/mock/mock_monotonic_clock.h"
#include "esphome/components/intex_common/mock/mock_serial.h"

namespace esphome {
namespace intex_eco5220g {

MATCHER_P(PointedElementsAreArray, expected, "") {
  return memcmp(arg, expected.data(), expected.size() * sizeof(expected[0])) == 0;
}

class IntexECO5220GTest : public ::testing::Test {
  protected:
    void SetUp() override {
      intex_eco5220g_.set_serial(&serial_);
      intex_eco5220g_.set_clock(&clock_);
    }
    intex_common::MockMonotonicClock clock_;
    intex_common::MockSerial serial_;
    IntexECO5220G intex_eco5220g_;
};

TEST_F(IntexECO5220GTest, PressPowerButton) {
  ButtonMessage message;
  message.set_button(ButtonMessage::Button::kTogglePower);
  auto raw = message.raw_message();
  EXPECT_CALL(serial_, send(PointedElementsAreArray(raw), raw.size()));
  intex_eco5220g_.press_power();
}

TEST_F(IntexECO5220GTest, PressToggleLockButton) {
  ButtonMessage message;
  message.set_button(ButtonMessage::Button::kToggleLock);
  auto raw = message.raw_message();
  EXPECT_CALL(serial_, send(PointedElementsAreArray(raw), raw.size()));
  intex_eco5220g_.press_toggle_lock();
}

TEST_F(IntexECO5220GTest, NoClock) {
  intex_eco5220g_.set_clock(nullptr);
  intex_eco5220g_.setup();
  EXPECT_TRUE((intex_eco5220g_.get_component_state() & Component::COMPONENT_STATE_FAILED) ==
              Component::COMPONENT_STATE_FAILED);
}

TEST_F(IntexECO5220GTest, NoSerial) {
  intex_eco5220g_.set_serial(nullptr);
  intex_eco5220g_.setup();
  EXPECT_TRUE((intex_eco5220g_.get_component_state() & Component::COMPONENT_STATE_FAILED) ==
              Component::COMPONENT_STATE_FAILED);
}

}  // namespace intex_eco5220g
}  // namespace esphome
