cmake_minimum_required(VERSION 3.16)
project(qwiet C)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Kconfig-based configuration
include(kconfig)

# Configuration files (semicolon-separated list, merged in order)
set(CONFIG "" CACHE STRING "Config files (e.g. configs/linux.conf;configs/testing.conf)")
set(CONFIG_EXTRA "" CACHE STRING "Extra config fragments to append")

if(NOT CONFIG)
    set(CONFIG "${CMAKE_SOURCE_DIR}/configs/linux.conf")
endif()

# Process Kconfig
kconfig_configure(
    KCONFIG_ROOT "${CMAKE_SOURCE_DIR}/Kconfig" CONFIG_FILES "${CONFIG}" EXTRA_CONFIGS ${CONFIG_EXTRA}
)

# Platform abstraction layer (composes traits based on Kconfig)
add_subdirectory(platform)

# Test support (CONFIG_TESTING=y in Kconfig)
if(CONFIG_TESTING)
    set(BUILD_TESTING ON)
    set(MEMORYCHECK_COMMAND_OPTIONS "--leak-check=full --track-fds=yes --error-exitcode=1")
    include(CTest)
    add_subdirectory(platform/testing/diode)
    add_subdirectory(tests/diode)
    add_subdirectory(tests/list)
    add_subdirectory(tests/macros)
    add_subdirectory(tests/sem)
    add_subdirectory(tests/timer)
endif()
