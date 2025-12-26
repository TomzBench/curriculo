# POSIX trait sources based on Kconfig
set(POSIX_SOURCES "")

if(CONFIG_PAL_POSIX_NET)
    list(APPEND POSIX_SOURCES src/net.c)
endif()

if(CONFIG_PAL_POSIX_SEM)
    list(APPEND POSIX_SOURCES src/sem.c)
endif()

if(CONFIG_PAL_POSIX_TIME)
    list(APPEND POSIX_SOURCES src/time.c)
endif()

add_library(qwiet_pal_posix ${POSIX_SOURCES})
target_include_directories(qwiet_pal_posix PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_kconfig(qwiet_pal_posix)
