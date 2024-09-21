#pragma once

/**
 * @file        config.h
 * 
 * @author      Federico Cristina <federico.cristina@outlook.it>
 * 
 * @copyright   Copyright (c) 2024 Federico Cristina
 *              
 *              This file is part of the calc scripting language project,
 *              under the Apache License v2.0. See LICENSE for license
 *              informations.
 * 
 * @brief       In this header are defined configuration macros and
 *              constants based on current environment informations.
 */

#ifndef CALC_CONFIG_H_
#define CALC_CONFIG_H_

#ifndef calcExpandMacro
/// @brief This macro expands the given macro only 'returning'
///        its value.
/// @param x Name of the macro of which expand the value.
/// @return x macro expanded.
#   define calcExpandMacro(x) x
#endif // calcExpandMacro

#ifndef calcConcatMacro
/// @brief This macro concatenates two other macros after
///        expanding them.
/// @param x Prefix macro in the concatenation.
/// @param y Suffix macro in the concatenation.
/// @return A concatenated token produced by xy.
#   define calcConcatMacro(x, y) calcExpandMacro(x) ## calcExpandMacro(y)
#endif // calcConcatMacro

// Versioning Infos

#ifndef CALC_VERSION_MAJOR
/// @brief This macro represents the first number of the
///        version string.
#   define CALC_VERSION_MAJOR 0
#endif // CALC_VERSION_MAJOR

#ifndef CALC_VERSION_MINOR
/// @brief This macro represents the second number of the
///        version string.
#   define CALC_VERSION_MINOR 1
#endif // CALC_VERSION_MINOR

#ifndef CALC_VERSION_PATCH
/// @brief This macro represents the third (and last)
///        number of the version string.
#   define CALC_VERSION_PATCH 0
#endif // CALC_VERSION_PATCH

#ifndef CALC_VERSION
/// @brief This macro represents the version string
///        to display when requested.
///
///        NOTE: To compare the version with another
///        could be better use a numeric version of
///        this macro. The numeric version of this
///        string (as hexadecimal number) can be the
///        macro CALC_VERSION_ID, please use it.
///
#   define CALC_VERSION "0.1.0"
#endif // CALC_VERSION

#ifndef CALC_VERSION_ID
/// @brief Numeric version of CALC_VERSION, this macro
///        represents an identifier hexadecimal number
///        made on the base of the version.
#   define CALC_VERSION_ID 0x0010
#endif // CALC_VERSION_ID

// Compiler Infos

/// @brief Unrecognized Compiler.
#define CALC_COMPILER_ID_NONE 0x00
/// @brief Microsoft Visual C/C++ Compiler.
#define CALC_COMPILER_ID_MSVC 0x02
/// @brief LLVM Clang Compiler.
#define CALC_COMPILER_ID_LLVM 0x04
/// @brief GNU C Compiler. (GNU Compiler Collection)
#define CALC_COMPILER_ID_GNUC 0x08

#ifndef CALC_COMPILER_ID
#   if   defined __clang__
/// @brief This macro holds the identifier of the compiler that's
///        compiling this source.
#       define CALC_COMPILER_ID CALC_COMPILER_ID_LLVM
#   elif defined _MSC_VER
/// @brief This macro holds the identifier of the compiler that's
///        compiling this source.
#       define CALC_COMPILER_ID CALC_COMPILER_ID_MSVC
#   elif defined __GNUC__
/// @brief This macro holds the identifier of the compiler that's
///        compiling this source.
#       define CALC_COMPILER_ID CALC_COMPILER_ID_GNUC
#   else
/// @brief This macro holds the identifier of the compiler that's
///        compiling this source.
#       define CALC_COMPILER_ID CALC_COMPILER_ID_NONE
#   endif
#endif // CALC_COMPILER_ID

#ifndef CALC_COMPILER_HAS_CCONVS
/// @brief This macro can be used to check if the compiler supports
///        calling conventions specification in Microsoft-style.
#   define CALC_COMPILER_HAS_CCONVS     ((CALC_COMPILER_ID == CALC_COMPILER_ID_LLVM) \
                                      || (CALC_COMPILER_ID == CALC_COMPILER_ID_MSVC))
#endif

#ifndef CALC_COMPILER_HAS_DECLSPEC
/// @brief This macro can be used to check if the compiler supports
///        __declspec attributes specification.
#   define CALC_COMPILER_HAS_DECLSPEC   ((CALC_COMPILER_ID == CALC_COMPILER_ID_LLVM) \
                                      || (CALC_COMPILER_ID == CALC_COMPILER_ID_MSVC))
#endif

// Platform Infos

/// @brief Unrecognized Platform.
#define CALC_PLATFORM_ID_NONE  0x00
/// @brief Microsoft Windows 32-bit.
#define CALC_PLATFORM_ID_WIN32 0x02
/// @brief Microsoft Windows 64-bit.
#define CALC_PLATFORM_ID_WIN64 0x04
/// @brief Unix or Unix-like Platform.
#define CALC_PLATFORM_ID_UNIX  0x08
/// @brief Linux Platform.
#define CALC_PLATFORM_ID_LINUX 0x10
/// @brief Mac OS X Platform.
#define CALC_PLATFORM_ID_MACOS 0x20

#ifndef CALC_PLATFORM_ID
#   if   defined _WIN64
/// @brief This macro holds the identifier of the platform on which
///        this source is compiled.
#       define CALC_PLATFORM_ID CALC_PLATFORM_ID_WIN64
#   elif defined _WIN32
/// @brief This macro holds the identifier of the platform on which
///        this source is compiled.
#       define CALC_PLATFORM_ID CALC_PLATFORM_ID_WIN32
#   elif defined __linux__
/// @brief This macro holds the identifier of the platform on which
///        this source is compiled.
#       define CALC_PLATFORM_ID CALC_PLATFORM_ID_LINUX
#   elif defined __mach__
/// @brief This macro holds the identifier of the platform on which
///        this source is compiled.
#       define CALC_PLATFORM_ID CALC_PLATFORM_ID_MACOS
#   elif defined __unix__
/// @brief This macro holds the identifier of the platform on which
///        this source is compiled.
#       define CALC_PLATFORM_ID CALC_PLATFORM_ID_UNIX
#   else
/// @brief This macro holds the identifier of the platform on which
///        this source is compiled.
#       define CALC_PLATFORM_ID CALC_PLATFORM_ID_NONE
#   endif
#endif // CALC_PLATFORM_ID

#ifndef CALC_PLATFORM_IS_WINDOWS
/// @brief This macro can be used to check if the current platform is
///        Windows.
#   define CALC_PLATFORM_IS_WINDOWS     ((CALC_PLATFORM_ID == CALC_PLATFORM_ID_WIN64) \
                                      || (CALC_PLATFORM_ID == CALC_PLATFORM_ID_WIN32))
#endif // CALC_PLATFORM_IS_WINDOWS

#ifndef CALC_PLATFORM_IS_UNIX
/// @brief This macro can be used to check if the current platform is
///        Unix-like.
#   define CALC_PLATFORM_IS_UNIX        ((CALC_PLATFORM_ID == CALC_PLATFORM_ID_UNIX)  \
                                      || (CALC_PLATFORM_ID == CALC_PLATFORM_ID_LINUX) \
                                      || (CALC_PLATFORM_ID == CALC_PLATFORM_ID_MACOS))
#endif // CALC_PLATFORM_IS_UNIX

// Other

#ifndef CALC_MAGICNUM
/// @brief CALC magic number...
#	define CALC_MAGICNUM 0x43414C43
#endif // CALC_MAGICNUM

#ifndef CALC_MAGICSTR
/// @brief CALC magic number...
#	define CALC_MAGICSTR "\x43\x41\x4C\x43"
#endif // CALC_MAGICSTR

#endif // CALC_CONFIG_H_
