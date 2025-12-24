find_package(Unity REQUIRED)
find_package(CMock REQUIRED)

add_library(curriculo_diode src/diode.c src/poll.c)
target_include_directories(curriculo_diode PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(curriculo_diode PUBLIC unity cmock PRIVATE curriculo_pal)
cmock_handle(curriculo_diode ${CMAKE_SOURCE_DIR}/include/curriculo/platform/net.h)
