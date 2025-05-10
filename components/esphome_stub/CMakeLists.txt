add_library(esphome_stub INTERFACE)
target_include_directories(esphome_stub INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include>
)
