set(HEADERS
    "hash.h"
)

set(SOURCES
    "hash.c"
)

calc_add_library(core
    SOURCES ${SOURCES}
    HEADERS ${HEADERS}
    DEPENDS base
    INSTALL
)
