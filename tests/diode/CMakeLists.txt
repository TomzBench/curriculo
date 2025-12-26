find_package(CMock REQUIRED)

# Cross-platform tests
set(TEST_SOURCES src/test_connect.c src/test_listen.c src/test_poll.c src/test_recv.c src/test_send.c)

# Linux-specific tests (now uses Kconfig)
if(CONFIG_DIODE_TEST_EVDEV)
    list(APPEND TEST_SOURCES src/test_evdev.c)
endif()

foreach(TEST_FILE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)

    test_runner_generate(${TEST_NAME} ${TEST_FILE})
    target_link_libraries(${TEST_NAME} PRIVATE qwiet_diode)
endforeach()
