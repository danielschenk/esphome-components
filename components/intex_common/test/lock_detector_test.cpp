#include "../lock_detector.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../mock/mock_monotonic_clock.h"

using ::testing::Return;

class LockDetectorTest : public ::testing::Test {
  protected:
    esphome::intex_common::MockMonotonicClock clock_;
    esphome::intex_common::LockDetector lock_detector_{clock_};
};

TEST_F(LockDetectorTest, TestInitialState) {
  EXPECT_FALSE(lock_detector_.is_locked().has_value());
}

TEST_F(LockDetectorTest, TestStartBlinking) {
  EXPECT_CALL(clock_, millis()).WillOnce(Return(1501)).WillOnce(Return(1502));

  lock_detector_.update(false, true);
  EXPECT_TRUE(*lock_detector_.is_locked());
  lock_detector_.update(true, true);
  EXPECT_FALSE(*lock_detector_.is_locked());
}

TEST_F(LockDetectorTest, TestStopBlinking) {
  EXPECT_CALL(clock_, millis())
      .WillOnce(Return(0))
      .WillOnce(Return(1))
      .WillOnce(Return(1499))
      .WillOnce(Return(1501));

  lock_detector_.update(true, true);
  EXPECT_FALSE(*lock_detector_.is_locked());

  lock_detector_.update(false, true);
  EXPECT_FALSE(*lock_detector_.is_locked());

  lock_detector_.update(false, true);
  EXPECT_FALSE(*lock_detector_.is_locked());

  lock_detector_.update(false, true);
  EXPECT_TRUE(*lock_detector_.is_locked());
}

TEST_F(LockDetectorTest, TestPowerOff) {
  EXPECT_CALL(clock_, millis()).WillOnce(Return(0)).WillOnce(Return(1501));

  lock_detector_.update(true, true);
  EXPECT_FALSE(*lock_detector_.is_locked());

  lock_detector_.update(true, false);
  EXPECT_TRUE(*lock_detector_.is_locked());
}
