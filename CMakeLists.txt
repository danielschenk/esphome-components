#
# NOTE: CMake is used for unit testing only! Firmware is built using esphome.
#

cmake_minimum_required(VERSION 3.14)
project(my_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/59c924bc471cefea25a7cf7eb40b6c101b170b12.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(EspHomeHelpers.cmake)

add_subdirectory(components/esphome_stub)
add_subdirectory(components/intex_common)
add_subdirectory(components/intex_eco5220g)

enable_testing()
