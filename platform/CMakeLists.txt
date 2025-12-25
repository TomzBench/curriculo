# Platform trait composition
# Each platform composes the traits it needs into qwiet_pal

if(PLATFORM STREQUAL "linux" OR PLATFORM STREQUAL "pinenote")
    add_subdirectory(posix)
    add_subdirectory(linux)

    # Add PLATFORM_LINUX to posix trait (needed for common.h)
    target_compile_definitions(qwiet_pal_posix PUBLIC PLATFORM_LINUX)

    # Composed library exposing all PAL symbols
    add_library(qwiet_pal INTERFACE)
    target_link_libraries(qwiet_pal INTERFACE qwiet_pal_posix qwiet_pal_linux)
endif()
