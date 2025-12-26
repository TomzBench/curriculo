# Platform trait composition based on Kconfig

if(CONFIG_PAL_POSIX)
    add_subdirectory(posix)
endif()

if(CONFIG_PAL_LINUX)
    add_subdirectory(linux)
endif()

# Composed library exposing all PAL symbols
add_library(qwiet_pal INTERFACE)

if(CONFIG_PAL_POSIX)
    target_link_libraries(qwiet_pal INTERFACE qwiet_pal_posix)
endif()

if(CONFIG_PAL_LINUX)
    target_link_libraries(qwiet_pal INTERFACE qwiet_pal_linux)
endif()

# Add kconfig header include path
target_kconfig(qwiet_pal)
