# Usage:
#
#   calc_add_unit_test(<TARGET>)
#
# Adds an unit-test executable.
#
function(calc_add_unit_test TARGET)
    get_property(_LIBS GLOBAL PROPERTY CALC_TARGETS)

    set(_OPTIONS INSTALL)
    set(_ONE_VAL DESTINATION)
    set(_MUL_VAL SOURCES DEPENDS)

    cmake_parse_arguments(_ARG
        "${_OPTIONS}"
        "${_ONE_VAL}"
        "${_MUL_VAL}"
         ${ARGV}
    )

    set(_ARG_NAME "${CALC_UNIT_TEST_PREFIX}${TARGET}")

    add_executable(${_ARG_NAME} "${_ARG_SOURCES}")

    if(_ARG_DEPENDS)
        target_link_libraries(${_ARG_NAME} "${_ARG_DEPENDS}")
    endif()

    if(_ARG_INSTALL)
        if(_ARG_DESTINATION)
            install(TARGETS ${_ARG_NAME} ${_ARG_DEPENDS} DESTINATION ${_ARG_DESTINATION})
        else()
            install(TARGETS ${_ARG_NAME} ${_ARG_DEPENDS})
        endif()
    endif()

    calc_log("add unit-test ${_ARG_NAME}")
endfunction()
