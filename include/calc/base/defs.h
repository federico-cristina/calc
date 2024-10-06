#pragma once

/**
 * @file        defs.h
 *
 * @author      Federico Cristina <federico.cristina@outlook.it>
 *
 * @copyright   Copyright (c) 2024 Federico Cristina
 *
 *              This file is part of the calc scripting language project,
 *              under the Apache License v2.0. See LICENSE for license
 *              informations.
 *
 * @brief       In this header are defined common macros and constants
 *              expecially the ones used to mark C++ files as extern "C",
 *              to control the right use of inline functions, the use of
 *              register keyword and the calling conventions, and finally,
 *              the macros regarding dll import/export and other attributes
 *              usage.
 */

#ifndef CALC_BASE_DEFS_H_
#define CALC_BASE_DEFS_H_

#ifndef _CRT_SECURE_NO_WARNINGS
/// @brief Disable CRT standard C library functions
///        deprecations. (This macro avoids errors and
///        warnings while compiling with MSVC compiler
///        or clang-cl on Windows)
#   define _CRT_SECURE_NO_WARNINGS 1
#endif // _CRT_SECURE_NO_WARNINGS

#include <stddef.h>

#ifndef CALC_C_HEADER_BEGIN
#   ifdef __cplusplus
#       if   defined _CRT_BEGIN_C_HEADER
/// @brief Marks the beginning of a C header file for C++
///        compilers.
#           define CALC_C_HEADER_BEGIN _CRT_BEGIN_C_HEADER
#       elif defined __cplusplus
/// @brief Marks the beginning of a C header file for C++
///        compilers.
#           define CALC_C_HEADER_BEGIN extern "C" {
#       else
/// @brief Marks the beginning of a C header file for C++
///        compilers.
#           define CALC_C_HEADER_BEGIN
#       endif
#   else
/// @brief Marks the beginning of a C header file for C++
///        compilers.
#       define CALC_C_HEADER_BEGIN
#   endif
#endif // CALC_C_HEADER_BEGIN

#ifndef CALC_C_HEADER_END
#   ifdef __cplusplus
#       if   defined _CRT_END_C_HEADER
/// @brief Marks the ending of a C header file for C++ compilers.
#           define CALC_C_HEADER_END _CRT_END_C_HEADER
#       elif defined __cplusplus
/// @brief Marks the ending of a C header file for C++ compilers.
#           define CALC_C_HEADER_END }
#       else
/// @brief Marks the ending of a C header file for C++ compilers.
#           define CALC_C_HEADER_END
#       endif
#   else
/// @brief Marks the ending of a C header file for C++ compilers.
#       define CALC_C_HEADER_END
#   endif
#endif // CALC_C_HEADER_END

#include "calc/config.h"

// Calling Conventions

#if CALC_PLATFORM_IS_WINDOWS && CALC_COMPILER_HAS_CCONVS
#   ifndef CALC_STDCALL
/// @brief __stdcall calling convention. (Enabled)
#       define CALC_STDCALL  __stdcall
#   endif // CALC_STDCALL

#   ifndef CALC_CDECL
/// @brief __cdecl calling convention. (Enabled)
#       define CALC_CDECL    __cdecl
#   endif // CALC_CDECL

#   ifndef CALC_FASTCALL
/// @brief __fastcall calling convention. (Enabled)
#       define CALC_FASTCALL  __fastcall
#   endif // CALC_FASTCALL
#else
#   ifndef CALC_STDCALL
/// @brief __stdcall calling convention. (Disabled)
#       define CALC_STDCALL
#   endif // CALC_STDCALL

#   ifndef CALC_CDECL
/// @brief __cdecl calling convention. (Disabled)
#       define CALC_CDECL
#   endif // CALC_CDECL

#   ifndef CALC_FASTCALL
/// @brief __fastcall calling convention. (Disabled)
#       define CALC_FASTCALL
#   endif // CALC_FASTCALL
#endif

// Attributes

#if CALC_PLATFORM_IS_WINDOWS && CALC_COMPILER_HAS_DECLSPEC
#   ifndef CALC_ATTRIBUTE
/// @brief Provides a __declspec attribute.
#       define CALC_ATTRIBUTE(attr) __declspec(attr)
#   endif // CALC_ATTRIBUTE
#else
#   ifndef CALC_ATTRIBUTE
/// @brief Provides an __attribute__ attribute.
#       define CALC_ATTRIBUTE(attr) __attribute__((attr))
#   endif // CALC_ATTRIBUTE
#endif

#ifndef CALC_NORETURN
/// @brief This macro specified that the function have not
///        any return statement.
#   define CALC_NORETURN CALC_ATTRIBUTE(noreturn)
#endif // CALC_NORETURN

#if CALC_PLATFORM_IS_WINDOWS
#   ifndef CALC_DLL_EXPORT
/// @brief This macro exports a symbol while building a dynamic
///        library.
#       define CALC_DLL_EXPORT CALC_ATTRIBUTE(dllexport)
#   endif // CALC_DLL_EXPORT

#   ifndef CALC_DLL_IMPORT
/// @brief This macro imports a symbol while building a dynamic
///        library.
#       define CALC_DLL_IMPORT CALC_ATTRIBUTE(dllimport)
#   endif // CALC_DLL_IMPORT

#   ifndef CALC_DLL_STATIC
/// @brief This macro hides a symbol while building a dynamic
///        library.
#       define CALC_DLL_STATIC
#   endif // CALC_DLL_STATIC
#else
#   if __GNUC__ >= 4
#       ifndef CALC_DLL_EXPORT
/// @brief This macro exports a symbol while building a dynamic
///        library.
#           define CALC_DLL_EXPORT CALC_ATTRIBUTE(visibility("default"))
#       endif // CALC_DLL_EXPORT

#       ifndef CALC_DLL_IMPORT
/// @brief This macro imports a symbol while building a dynamic
///        library.
#           define CALC_DLL_IMPORT CALC_ATTRIBUTE(visibility("default"))
#       endif // CALC_DLL_IMPORT

#       ifndef CALC_DLL_STATIC
/// @brief This macro hides a symbol while building a dynamic
///        library.
#           define CALC_DLL_STATIC CALC_ATTRIBUTE(visibility("hidden"))
#       endif // CALC_DLL_STATIC
#   else
#       ifndef CALC_DLL_EXPORT
/// @brief This macro exports a symbol while building a dynamic
///        library.
#           define CALC_DLL_EXPORT
#       endif // CALC_DLL_EXPORT

#       ifndef CALC_DLL_IMPORT
/// @brief This macro imports a symbol while building a dynamic
///        library.
#           define CALC_DLL_IMPORT
#       endif // CALC_DLL_IMPORT

#       ifndef CALC_DLL_STATIC
/// @brief This macro hides a symbol while building a dynamic
///        library.
#           define CALC_DLL_STATIC
#       endif // CALC_DLL_STATIC
#   endif
#endif

// Other

#ifndef CALC_DEBUG
#   if defined DEBUG || defined _DEBUG
/// @brief Internal debug flag.
#       define CALC_DEBUG 1
#   else
/// @brief Internal debug flag.
#       define CALC_DEBUG 0
#   endif
#endif // CALC_DEBUG

#ifndef CALC_BUILD_AS_DLL
#   if (defined DLL || defined _DLL) && CALC_PLATFORM_IS_WINDOWS
/// @brief Internal DLL flag.
#       define CALC_BUILD_AS_DLL 1
#   else
/// @brief Internal DLL flag.
#       define CALC_BUILD_AS_DLL 0
#   endif
#endif // CALC_BUILD_AS_DLL

#ifndef CALC_REGISTER
#   if defined __cplusplus && (__cplusplus >= 201703L)
/// @brief Register storage, in C, adivises the compiler to
///        store that variable in a processor register instead
///        of memory. The compiler may or may not follow this
///        hint.
///
/// @note  In C++17 the register keyword is deprecated and out
///        of support. So since that version is not useful
///        specify it.
///
#       define CALC_REGISTER
#   else
/// @brief Register storage, in C, adivises the compiler to
///        store that variable in a processor register instead
///        of memory. The compiler may or may not follow this
///        hint.
///
/// @note  In C++17 the register keyword is deprecated and out
///        of support. So since that version is not useful
///        specify it.
///
#       define CALC_REGISTER register
#   endif
#endif // CALC_REGISTER

#ifndef CALC_INLINE
#   if (CALC_COMPILER_ID == CALC_COMPILER_ID_GNUC) || CALC_PLATFORM_IS_UNIX
/// @brief Inline function specifier for inline functions
///        declared in the header file.
#       define CALC_INLINE static inline
#   else
/// @brief Inline function specifier for inline functions
///        declared in the header file.
#       define CALC_INLINE inline
#   endif
#endif // CALC_INLINE

#ifndef CALC_EXTERN
/// @brief Marks a function that is not defined in the current
///        header.
#   define CALC_EXTERN extern
#endif // CALC_EXTERN

#endif // CALC_BASE_DEFS_H_
