find_package(PkgConfig)
pkg_check_modules(LIBFFI REQUIRED IMPORTED_TARGET libffi)

include(calc_add_libary)
