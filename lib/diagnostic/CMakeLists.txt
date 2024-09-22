set(HEADERS
    "diagnostics.h"
)

set(SOURCES
    "diagnostics.c"
)

calc_add_library(diagnostic
    SOURCES ${SOURCES}
    HEADERS ${HEADERS}
    DEPENDS base
    INSTALL
)
