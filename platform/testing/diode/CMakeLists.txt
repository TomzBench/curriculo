find_package(Unity REQUIRED)
find_package(CMock REQUIRED)

add_library(qwiet_diode src/diode.c src/poll.c)
target_include_directories(qwiet_diode PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(qwiet_diode PUBLIC unity cmock PRIVATE qwiet_pal)
cmock_handle(qwiet_diode ${CMAKE_SOURCE_DIR}/include/qwiet/platform/net.h)
