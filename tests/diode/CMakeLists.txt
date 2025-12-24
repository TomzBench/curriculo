find_package(CMock REQUIRED)

set(TEST_SOURCES src/test_connect.c src/test_listen.c src/test_poll.c src/test_recv.c src/test_send.c)

foreach(TEST_FILE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)

    test_runner_generate(${TEST_NAME} ${TEST_FILE})
    target_include_directories(${TEST_NAME} PRIVATE src)
    target_link_libraries(${TEST_NAME} PRIVATE qwiet_diode)
endforeach()
