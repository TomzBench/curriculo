# Kconfig Integration for CMake
#
# Provides:
#   kconfig_configure() - Process Kconfig and generate config header
#   target_kconfig()    - Add kconfig header include path to target
#
# Usage:
#   include(kconfig)
#   kconfig_configure(
#       KCONFIG_ROOT "${CMAKE_SOURCE_DIR}/Kconfig"
#       CONFIG_FILE "${CMAKE_SOURCE_DIR}/prj.conf"
#   )

include_guard(GLOBAL)

find_program(UV_EXECUTABLE uv REQUIRED)

set(KCONFIG_GENCONFIG_PY "${CMAKE_SOURCE_DIR}/tools/kconfig/genconfig.py")

# Generate config header and CMake variables from Kconfig
#
# Usage:
#   kconfig_configure(
#       KCONFIG_ROOT path/to/Kconfig
#       CONFIG_FILES "config1.conf;config2.conf"
#       EXTRA_CONFIGS config3.conf config4.conf
#   )
#
# CONFIG_FILES can be a semicolon-separated list (merged in order).
# EXTRA_CONFIGS are appended after CONFIG_FILES.
#
# Generates:
#   ${CMAKE_BINARY_DIR}/include/qwiet/kconfig.h - C header with #define CONFIG_*
#   ${CMAKE_BINARY_DIR}/kconfig.cmake           - CMake file with set(CONFIG_*)
function(kconfig_configure)
    cmake_parse_arguments(KCONFIG "" "KCONFIG_ROOT" "CONFIG_FILES;EXTRA_CONFIGS" ${ARGN})

    if(NOT KCONFIG_KCONFIG_ROOT)
        set(KCONFIG_KCONFIG_ROOT "${CMAKE_SOURCE_DIR}/Kconfig")
    endif()

    set(KCONFIG_OUTPUT_HEADER "${CMAKE_BINARY_DIR}/include/qwiet/kconfig.h")
    set(KCONFIG_OUTPUT_CMAKE "${CMAKE_BINARY_DIR}/kconfig.cmake")

    # Build command
    set(GENCONFIG_CMD
        ${UV_EXECUTABLE}
        run
        python
        ${KCONFIG_GENCONFIG_PY}
        --kconfig-root
        ${KCONFIG_KCONFIG_ROOT}
        --header
        ${KCONFIG_OUTPUT_HEADER}
        --cmake
        ${KCONFIG_OUTPUT_CMAKE}
    )

    # Add config files (supports semicolon-separated list)
    foreach(CONF ${KCONFIG_CONFIG_FILES})
        if(NOT IS_ABSOLUTE "${CONF}")
            set(CONF "${CMAKE_SOURCE_DIR}/${CONF}")
        endif()
        if(EXISTS "${CONF}")
            list(APPEND GENCONFIG_CMD --config ${CONF})
        endif()
    endforeach()

    # Add extra config fragments
    foreach(EXTRA_CONF ${KCONFIG_EXTRA_CONFIGS})
        if(NOT IS_ABSOLUTE "${EXTRA_CONF}")
            set(EXTRA_CONF "${CMAKE_SOURCE_DIR}/${EXTRA_CONF}")
        endif()
        if(EXISTS "${EXTRA_CONF}")
            list(APPEND GENCONFIG_CMD --config ${EXTRA_CONF})
        endif()
    endforeach()

    # Ensure output directory exists
    get_filename_component(HEADER_DIR ${KCONFIG_OUTPUT_HEADER} DIRECTORY)
    file(MAKE_DIRECTORY ${HEADER_DIR})

    # Execute at configure time
    execute_process(
        COMMAND ${GENCONFIG_CMD}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        RESULT_VARIABLE RESULT
        OUTPUT_VARIABLE OUTPUT
        ERROR_VARIABLE ERROR
    )

    if(NOT RESULT EQUAL 0)
        message(FATAL_ERROR "Kconfig generation failed: ${ERROR}")
    endif()

    # Include generated CMake variables in PARENT_SCOPE
    # Read the file and set each variable in parent scope
    file(STRINGS ${KCONFIG_OUTPUT_CMAKE} CONFIG_LINES)
    foreach(LINE ${CONFIG_LINES})
        if(LINE MATCHES "^set\\(([^ ]+) ([^)]+)\\)")
            set(VAR_NAME ${CMAKE_MATCH_1})
            set(VAR_VALUE ${CMAKE_MATCH_2})
            set(${VAR_NAME} ${VAR_VALUE} PARENT_SCOPE)
        endif()
    endforeach()

    # Export header path for targets (GLOBAL so functions can access)
    set(KCONFIG_HEADER_DIR ${HEADER_DIR} PARENT_SCOPE)
    set_property(GLOBAL PROPERTY KCONFIG_HEADER_DIR ${HEADER_DIR})
endfunction()

# Add kconfig header include path to target
#
# Usage:
#   target_kconfig(my_target)
#
# Adds ${CMAKE_BINARY_DIR}/include to target's include directories.
function(target_kconfig TARGET)
    get_property(KCONFIG_HEADER_DIR GLOBAL PROPERTY KCONFIG_HEADER_DIR)
    get_target_property(TARGET_TYPE ${TARGET} TYPE)
    if(TARGET_TYPE STREQUAL "INTERFACE_LIBRARY")
        target_include_directories(${TARGET} INTERFACE ${KCONFIG_HEADER_DIR}/..)
    else()
        target_include_directories(${TARGET} PUBLIC ${KCONFIG_HEADER_DIR}/..)
    endif()
endfunction()
