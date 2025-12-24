find_package(CMock REQUIRED)

test_runner_generate(test_sem src/test.c)

target_include_directories(test_sem PRIVATE src)
target_link_libraries(test_sem PRIVATE qwiet_pal unity)

