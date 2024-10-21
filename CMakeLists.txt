cmake_minimum_required(VERSION 3.10.0)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    project("calc"
        VERSION   0.1.1
        LANGUAGES C
    )

    set(CMAKE_C_EXTENSIONS        OFF)
    set(CMAKE_C_STANDARD          90)
    set(CMAKE_C_STANDARD_REQUIRED ON)
endif()

option(CALC_BUILD_SHARED_LIBRARIES "Build shared libaries." OFF)
option(CALC_ENABLE_UNIT_TESTS "Enables unit tests targets." ON)

if(CALC_BUILD_SHARED_LIBRARIES)
    set(WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
endif()

set(CALC_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

set(CALC_MODULES_DIR "${CALC_DIR}/cmake/modules")
set(CALC_INCLUDE_DIR "${CALC_DIR}/include")
set(CALC_LIBRARY_DIR "${CALC_DIR}/lib")
set(CALC_RUNTIME_DIR "${CALC_DIR}/runtime")

list(APPEND CMAKE_MODULE_PATH "${CALC_MODULES_DIR}")

set(CALC_CONFIG_PATH "${CALC_INCLUDE_DIR}/calc/config.h")

include(calc)

configure_file("${CALC_CONFIG_PATH}.in" "${CALC_CONFIG_PATH}")
calc_log("config file ${CALC_CONFIG_PATH}")

include_directories("${CALC_INCLUDE_DIR}")

add_subdirectory(lib)
add_subdirectory(src)

if(CALC_ENABLE_UNIT_TESTS)
    add_subdirectory(units)
endif()
