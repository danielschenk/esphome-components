# Mimics some of the ESPHome build system, such as putting header files at expected
# locations so that includes work as expected.
function(esphome_component target)
  get_target_property(SOURCES ${target} SOURCES)
  foreach(SOURCE ${SOURCES})
    if(SOURCE MATCHES "\\.(h|hpp|hh|hxx)$")
      set(TARGET_DIR "${CMAKE_BINARY_DIR}/include/esphome/components/${target}")
      file(COPY "${SOURCE}" DESTINATION "${TARGET_DIR}")
    endif()
  endforeach()

  target_include_directories(${target} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include>
  )
endfunction()
