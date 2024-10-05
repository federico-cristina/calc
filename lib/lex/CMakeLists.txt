set(HEADERS
    "tokens.h"
)

set(SOURCES
    "tokens.c"
)

calc_add_library(lex
    SOURCES ${SOURCES}
    HEADERS ${HEADERS}
    DEPENDS source diagnostic
    INSTALL
)
