add_library(qwiet_pal_posix src/net.c src/sem.c src/time.c)
target_include_directories(qwiet_pal_posix PUBLIC ${CMAKE_SOURCE_DIR}/include)
