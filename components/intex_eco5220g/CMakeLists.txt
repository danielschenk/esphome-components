enable_testing()

add_library(
  intex_eco5220g
  button_message.cpp
  display_message.cpp
)

add_executable(
  intex_eco5220g_test
  test/button_message_test.cpp
  test/display_message_test.cpp
)

target_link_libraries(
  intex_eco5220g_test
  intex_common
)

target_link_libraries(
  intex_eco5220g_test
  intex_eco5220g
  GTest::gtest_main
  GTest::gmock_main
)

include(GoogleTest)
gtest_discover_tests(intex_eco5220g_test)
