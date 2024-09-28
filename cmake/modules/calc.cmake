define_property(GLOBAL PROPERTY CALC_TARGETS)
define_property(GLOBAL PROPERTY CALC_LIBRARY)

set(CALC_LOG_PREFIX       "calc")
set(CALC_LIBRARY_PREFIX   "calc-lib-")
set(CALC_UNIT_TEST_PREFIX "calc-test-")

set(CMAKE_STATIC_LIBRARY_PREFIX ${CALC_LIBRARY_PREFIX})
set(CMAKE_SHARED_LIBRARY_PREFIX ${CALC_LIBRARY_PREFIX})
set(CMAKE_IMPORT_LIBRARY_PREFIX ${CALC_LIBRARY_PREFIX})

set(CALC_INCLUDE_PREFIX "${CALC_INCLUDE_DIR}/calc")

include(calc_log)
include(calc_add_library)
include(calc_add_unit_test)
include(calc_link_libraries)
