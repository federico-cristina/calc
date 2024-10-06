set(HEADERS
    "base64.h"
    "sha256.h"
    "hash.h"
)

set(SOURCES
    "base64.c"
    "sha256.c"
    "hash.c"
)

calc_add_library(core
    SOURCES ${SOURCES}
    HEADERS ${HEADERS}
    DEPENDS base
    INSTALL
)
