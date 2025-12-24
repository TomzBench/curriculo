find_package(Unity REQUIRED)
find_package(CMock REQUIRED)

# Core cross-platform sources
set(DIODE_SOURCES src/diode.c src/net_poll.c)

# Platform-specific sources
if(PLATFORM STREQUAL "linux")
    list(APPEND DIODE_SOURCES src/input_evdev.c)
endif()

add_library(qwiet_diode ${DIODE_SOURCES})
target_link_libraries(qwiet_diode PUBLIC unity cmock qwiet_pal)

# Cross-platform mocks
cmock_handle(qwiet_diode ${CMAKE_SOURCE_DIR}/include/qwiet/platform/net.h)

# Linux-specific mocks
if(PLATFORM STREQUAL "linux")
    cmock_handle(qwiet_diode ${CMAKE_SOURCE_DIR}/include/qwiet/platform/linux/input_evdev.h)
endif()
