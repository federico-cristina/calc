set(HEADERS
    "diagnostics.h"
    "emitter.h"
)

set(SOURCES
    "diagnostics.c"
    "emitter.c"
)

calc_add_library(diagnostic
    SOURCES ${SOURCES}
    HEADERS ${HEADERS}
    DEPENDS base
    INSTALL
)
