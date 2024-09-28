set(HEADERS
    "source_buffer.h"
    "source_location.h"
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
