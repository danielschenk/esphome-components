enable_testing()

add_executable(
  intex_eco5220g_test
  button_message.cpp
  display_message.cpp
  test/button_message_test.cpp
  test/display_message_test.cpp
)

target_link_libraries(
  intex_eco5220g_test
  GTest::gtest_main
  GTest::gmock_main
)

include(GoogleTest)
gtest_discover_tests(intex_eco5220g_test)
