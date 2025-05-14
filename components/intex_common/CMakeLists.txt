enable_testing()

add_library(
  intex_common
  STATIC
  common_hmi.h
  lock_detector.cpp
  lock_detector.h
  monotonic_clock.h
  serial.cpp
  serial.h
  timer_immobilizer.cpp
  timer_immobilizer.h

  mock/mock_monotonic_clock.h
  mock/mock_serial.h
)
esphome_component(intex_common)

target_link_libraries(
  intex_common
  esphome_stub
)

add_executable(
  intex_common_test
  test/lock_detector_test.cpp
)
target_link_libraries(
  intex_common_test
  intex_common
  GTest::gtest_main
  GTest::gmock_main
)

include(GoogleTest)
gtest_discover_tests(intex_common_test)
