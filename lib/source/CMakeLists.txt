set(HEADERS
    "source_buffer.h"
)

set(SOURCES
    "source_buffer.c"
)

calc_add_library(source
    SOURCES ${SOURCES}
    HEADERS ${HEADERS}
    DEPENDS base
    INSTALL
)
