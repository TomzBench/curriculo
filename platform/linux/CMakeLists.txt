# Linux trait sources based on Kconfig
set(LINUX_SOURCES "")

if(CONFIG_PAL_LINUX_EVENT)
    list(APPEND LINUX_SOURCES src/event.c)
endif()

if(CONFIG_PAL_LINUX_EVDEV)
    find_package(Libevdev REQUIRED)
    list(APPEND LINUX_SOURCES src/input_evdev.c)
endif()

if(CONFIG_PAL_LINUX_TIMER)
    list(APPEND LINUX_SOURCES src/timer.c)
endif()

add_library(qwiet_pal_linux ${LINUX_SOURCES})
target_include_directories(qwiet_pal_linux PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_kconfig(qwiet_pal_linux)

if(CONFIG_PAL_LINUX_EVDEV)
    target_link_libraries(qwiet_pal_linux PUBLIC libevdev::libevdev)
endif()
