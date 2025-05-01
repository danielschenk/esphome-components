enable_testing()

add_executable(
  intex_eco5220g_test
  display_message.cpp
  test/display_message_test.cpp
)

target_link_libraries(
  intex_eco5220g_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(intex_eco5220g_test)
