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
    "alloc.h"
    "string.h"
    "file.h"
    "utf8.h"
)

set(SOURCES
    "errno.c"
    "error.c"
    "dload.c"
    "string.c"
    "file.c"
    "utf8.c"
)

calc_add_library(base
    SOURCES ${SOURCES}
    HEADERS ${HEADERS}
    INSTALL
)
