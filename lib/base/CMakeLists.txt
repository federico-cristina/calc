set(HEADERS
    "defs.h"
    "bool.h"
    "utils.h"
    "byte.h"
    "api.h"
    "errno.h"
    "error.h"
    "bits.h"
    "dload.h"
)

set(SOURCES
    "errno.c"
    "error.c"
    "dload.c"
)

calc_add_library(base
    SOURCES ${SOURCES}
    HEADERS ${HEADERS}
    INSTALL
)
