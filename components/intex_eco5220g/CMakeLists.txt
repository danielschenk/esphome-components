enable_testing()

add_library(
  intex_eco5220g
  STATIC
  button_message.cpp
  button_message.h
  display_message.cpp
  display_message.h
  intex_eco5220g.cpp
  intex_eco5220g.h
)

add_executable(
  intex_eco5220g_test
  test/button_message_test.cpp
  test/display_message_test.cpp
  test/intex_eco5220g_test.cpp
)

target_link_libraries(
  intex_eco5220g
  intex_common
  esphome_stub
)

target_link_libraries(
  intex_eco5220g_test
  intex_eco5220g
  GTest::gtest_main
  GTest::gmock_main
)

include(GoogleTest)
gtest_discover_tests(intex_eco5220g_test)
