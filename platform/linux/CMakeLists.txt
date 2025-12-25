find_package(Libevdev REQUIRED)

add_library(qwiet_pal_linux src/event.c src/input_evdev.c src/timer.c)
target_include_directories(qwiet_pal_linux PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_compile_definitions(qwiet_pal_linux PUBLIC PLATFORM_LINUX)
target_link_libraries(qwiet_pal_linux PUBLIC libevdev::libevdev)
