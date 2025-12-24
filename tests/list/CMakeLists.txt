find_package(CMock REQUIRED)

test_runner_generate(test_list src/test.c)

target_include_directories(test_list PRIVATE src)
target_include_directories(test_list PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(test_list PRIVATE unity)
