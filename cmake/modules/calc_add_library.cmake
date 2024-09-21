define_property(GLOBAL PROPERTY CALC_TARGETS)
define_property(GLOBAL PROPERTY CALC_LIBRARY)

set(CALC_LIBRARY_PREFIX "calc-lib-")

set(CMAKE_STATIC_LIBRARY_PREFIX ${CALC_LIBRARY_PREFIX})
set(CMAKE_SHARED_LIBRARY_PREFIX ${CALC_LIBRARY_PREFIX})
set(CMAKE_IMPORT_LIBRARY_PREFIX ${CALC_LIBRARY_PREFIX})

set(CALC_INCLUDE_PREFIX "${CALC_INCLUDE_DIR}/calc")

# Usage:
#
#   calc_add_library(<TARGET> SOURCES <SOURCES> [HEADERS <HEADERS>] [STATIC|SHARED] [DEPENDS <DEPENDENCIES>] [[INSTALL] [DESTINATION <PATH>]])
#
# Adds a library target with calc specific naming and appends it into the global
# properties CALC_LIBRARY and CALC_TARGETS.
#
function(calc_add_libary TARGET)
    set(_OPTIONS STATIC SHARED INSTALL)
    set(_ONE_VAL DESTINATION)
    set(_MUL_VAL SOURCES HEADERS DEPENDS)

    cmake_parse_arguments(_ARG
        "${_OPTIONS}"
        "${_ONE_VAL}"
        "${_MUL_VAL}"
         ${ARGV}
    )

    set(_LIB_NAME "${CALC_LIBRARY_PREFIX}${TARGET}")

    if(_ARG_HEADERS AND NOT _ARG_SOURCES)
        set(_LIB_TYPE INTERFACE)
    elseif(_ARG_STATIC AND _ARG_SHARED)
        set(_LIB_TYPE STATIC SHARED)
    elseif(_ARG_STATIC)
        set(_LIB_TYPE STATIC)
    elseif(_ARG_SHARED)
        set(_LIB_TYPE SHARED)
    else()
        set(_LIB_TYPE ${CALC_DEFAULT_LIB_TYPE})
    endif()

    set(_LIB_HEADERS "")

    if(_ARG_HEADERS)
        foreach(_ARG_HEADER ${_ARG_HEADERS})
            list(APPEND _LIB_HEADERS "${CALC_INCLUDE_PREFIX}/${TARGET}/${_ARG_HEADER}")
        endforeach()
    endif()

    add_library(${TARGET} ${_LIB_TYPE} "${_LIB_HEADERS};${_ARG_SOURCES}")

    if(_ARG_DEPENDS)
        target_link_libraries(${TARGET} ${_ARG_DEPENDS})
    endif()

    if(_ARG_INSTALL)
        if(_ARG_DESTINATION)
            install(TARGETS ${TARGET} ${_ARG_DEPENDS} DESTINATION ${_ARG_DESTINATION})
        else()
            install(TARGETS ${TARGET} ${_ARG_DEPENDS})
        endif()
    endif()

    set_property(GLOBAL APPEND PROPERTY NOX_TARGETS "${TARGET}")
    set_property(GLOBAL APPEND PROPERTY NOX_LIBRARY "${_LIB_NAME}")

    message(NOTICE "${CALC_LOG_PREFIX}: Added ${_LIB_NAME}")
endfunction()
