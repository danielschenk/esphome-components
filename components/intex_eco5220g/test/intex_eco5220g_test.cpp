#include "../intex_eco5220g.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "mock/mock_serial.h"

class IntexECO5220GTest : public ::testing::Test {
  protected:
    void SetUp() override {
      // Set up the mock serial object
      mock_serial_ = new intex_common::MockSerial();
      intex_eco5220g_.set_serial(mock_serial_);
    }

    void TearDown() override { delete mock_serial_; }

    intex_eco5220g::IntexECO5220G intex_eco5220g_;
    intex_common::MockSerial *mock_serial_;
};
