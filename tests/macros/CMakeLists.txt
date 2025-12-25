find_package(CMock REQUIRED)

test_runner_generate(test_macros src/test.c)

target_include_directories(test_macros PRIVATE src)
target_include_directories(test_macros PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(test_macros PRIVATE unity)
