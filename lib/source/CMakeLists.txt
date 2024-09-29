set(HEADERS
    "source_buffer.h"
    "source_location.h"
    "source_stream.h"
)

set(SOURCES
    "source_buffer.c"
    "source_stream.c"
)

calc_add_library(source
    SOURCES ${SOURCES}
    HEADERS ${HEADERS}
    DEPENDS base
    INSTALL
)
