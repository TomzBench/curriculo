find_package(Unity REQUIRED)
find_package(CMock REQUIRED)

# Core cross-platform sources
set(DIODE_SOURCES src/diode.c src/net_poll.c)

# Platform-specific sources (now uses Kconfig)
if(CONFIG_PAL_LINUX_EVDEV)
    list(APPEND DIODE_SOURCES src/input/evdev.c)
endif()

add_library(qwiet_diode ${DIODE_SOURCES})
target_link_libraries(qwiet_diode PUBLIC unity cmock qwiet_pal)

# Cross-platform mocks
cmock_handle(qwiet_diode ${CMAKE_SOURCE_DIR}/include/qwiet/platform/posix/net.h)

# Linux-specific mocks (now uses Kconfig)
if(CONFIG_PAL_LINUX_EVDEV)
    cmock_handle(qwiet_diode ${CMAKE_CURRENT_SOURCE_DIR}/mocks/libevdev.h)
endif()
