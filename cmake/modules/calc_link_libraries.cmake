# Usage:
#
#   calc_link_libraries(<TARGET>)
#
# Links calc libraries to the specified target.
#
function(calc_link_libraries TARGET)
    get_property(_LIBS GLOBAL PROPERTY CALC_TARGETS)
    target_link_libraries(${TARGET} "${_LIBS}")
    calc_log("linked libraries to ${TARGET}")
endfunction()
