calc_add_unit_test(sha256
    SOURCES "test_sha256.c"
    DEPENDS core
    TEST
)

calc_add_unit_test(base64
    SOURCES "test_base64.c"
    DEPENDS core
    TEST
)
