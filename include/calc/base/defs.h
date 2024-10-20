#pragma once

/**
 * @file        defs.h
 *
 * @author      Federico Cristina <federico.cristina@outlook.it>
 *
 * @copyright   Copyright (c) 2024 Federico Cristina
 *
 *              This file is part of the calc programming language project,
 *              under the Apache License v2.0. See LICENSE file for license
 *              informations.
 *
 * @version     1.1
 *
 * @brief       In this header are defined commonly used constants and macros
 *              in the whole project.
 */

#ifndef CALC_BASE_DEFS_H_
#define CALC_BASE_DEFS_H_

#ifndef _CRT_SECURE_NO_WARNINGS
/**
 * @brief       Disable CRT standard C library functions deprecations. (This
 *              constant avoids errors and warnings while compiling with MSVC
 *              compiler, or clang-cl on Windows)
 */
#   define _CRT_SECURE_NO_WARNINGS 1
#endif

#include <stddef.h>

#ifndef CALC_C_HEADER_BEGIN
#   ifdef __cplusplus
#       if   defined _CRT_BEGIN_C_HEADER
/**
 * @brief       Marks the beginning of a C header file for C++ compilers.
 */
#           define CALC_C_HEADER_BEGIN _CRT_BEGIN_C_HEADER
#       elif defined __cplusplus
/**
 * @brief       Marks the beginning of a C header file for C++ compilers.
 */
#           define CALC_C_HEADER_BEGIN extern "C" {
#       else
/**
 * @brief       Marks the beginning of a C header file for C++ compilers.
 */
#           define CALC_C_HEADER_BEGIN
#       endif
#   else
/**
 * @brief       Marks the beginning of a C header file for C++ compilers.
 */
#       define CALC_C_HEADER_BEGIN
#   endif
#endif

#ifndef CALC_C_HEADER_END
#   ifdef __cplusplus
#       if   defined _CRT_END_C_HEADER
/**
 * @brief       Marks the end of a C header file for C++ compilers.
 */
#           define CALC_C_HEADER_END _CRT_END_C_HEADER
#       elif defined __cplusplus
/**
 * @brief       Marks the end of a C header file for C++ compilers.
 */
#           define CALC_C_HEADER_END }
#       else
/**
 * @brief       Marks the end of a C header file for C++ compilers.
 */
#           define CALC_C_HEADER_END
#       endif
#   else
/**
 * @brief       Marks the end of a C header file for C++ compilers.
 */
#       define CALC_C_HEADER_END
#   endif
#endif

#include "calc/config.h"

#ifndef calcExpandMacro
/**
 * @brief       This macro gets its parameter back, expanding it if it's a
 *              symbolic constant.
 *
 * @param       x       The value to get back.
 * @return      The value of the `x` parameter.
 */
#   define calcExpandMacro(x) x
#endif

#ifndef calcConcatMacro
/**
 * @brief       This macro concatenates the given tokens, if their constants
 *              they will be expanded.
 *
 * @param       x       Prefix token sequence.
 * @param       y       Suffix token sequence.
 * @return      The concatenated token sequence.
 */
#   define calcConcatMacro(x, y) calcExpandMacro(x) ## calcExpandMacro(y)
#endif

#ifndef calc_MacroToString
/**
 * @brief       This macro gets a string version of the parameter token.
 * @attention   THIS IS ONLY AN HELPER MACRO DON'T USE IT DIRECTLY.
 */
#   define calc_MacroToString(x) #x
#endif

#ifndef calcMacroToString
/**
 * @brief       This macro gets a string version of the given token sequence.
 *
 * @param       x       Token sequence to stringify.
 * @return      A string version of the `x` parameter.
 */
#   define calcMacroToString(x) calc_MacroToString(x)
#endif

/**
 * @defgroup    CALLING_CONVENTIONS Calling Conventions
 * @{
 */

#pragma region Calling Conventions

#ifndef CALC_STDCALL
#   if CALC_PLATFORM_IS_WINDOWS && CALC_COMPILER_HAS_CCONVS
/**
 * @brief       This constant provides __stdcall calling convention on systems
 *              and compilers that supports it.
 */
#       define CALC_STDCALL __stdcall
#   else
/**
 * @brief       This constant provides __stdcall calling convention on systems
 *              and compilers that supports it.
 */
#       define CALC_STDCALL 
#   endif
#endif

#ifndef CALC_CDECL
#   if CALC_PLATFORM_IS_WINDOWS && CALC_COMPILER_HAS_CCONVS
/**
 * @brief       This constant provides __cdecl calling convention on systems
 *              and compilers that supports it.
 */
#       define CALC_CDECL __cdecl
#   else
/**
 * @brief       This constant provides __cdecl calling convention on systems
 *              and compilers that supports it.
 */
#       define CALC_CDECL
#   endif
#endif

#pragma endregion

/**
 * @}
 * 
 * @defgroup    ATTRIBUTES Attributes
 * @{
 */

#pragma region Attributes

#ifndef CALC_ATTRIBUTE
#   if CALC_C_EXTENSIONS
#       if CALC_PLATFORM_IS_WINDOWS && CALC_COMPILER_HAS_DECLSPEC
/**
 * @brief       This macro provides compiler specific attributes or,
 *              if disabled C extensions, this macro does nothing.
 */
#           define CALC_ATTRIBUTE(attr) __declspec(attr)
#       else
/**
 * @brief       This macro provides compiler specific attributes or,
 *              if disabled C extensions, this macro does nothing.
 */
#           define CALC_ATTRIBUTE(attr) __attribute__((attr))
#       endif
#   else
/**
 * @brief       This macro provides compiler specific attributes or,
 *              if disabled C extensions, this macro does nothing.
 */
#       define CALC_ATTRIBUTE(attr)
#   endif
#endif

#ifndef CALC_NORETURN
#   if CALC_C_STANDARD < CALC_C_STANDARD_C23
/**
 * @brief       This macro provides `noreturn` attribute.
 */
#       define CALC_NORETURN CALC_ATTRIBUTE(noreturn)
#   else
/**
 * @brief       This macro provides `noreturn` attribute.
 */
#       define CALC_NORETURN [[noreturn]]
#   endif
#endif

#ifndef CALC_DEPRECATED
#   if CALC_C_STANDARD < CALC_C_STANDARD_C23
/**
 * @brief       This macro provides `deprecated` attribute.
 */
#       define CALC_DEPRECATED(reason) CALC_ATTRIBUTE(deprecated(reason))
#   else
/**
 * @brief       This macro provides `deprecated` attribute.
 */
#       define CALC_DEPRECATED(reason) [[deparecated(reason)]]
#   endif
#endif

#ifndef CALC_DLL_EXPORT
#   if CALC_PLATFORM_IS_WINDOWS
/**
 * @brief       This macro provides compiler specific `dllexport` attribute
 *              to deal with shared library functions exportations, only if
 *              supported.
 */
#       define CALC_DLL_EXPORT CALC_ATTRIBUTE(dllexport)
#   elif (CALC_COMPILER_ID == CALC_COMPILER_ID_GNUC) && (__GNUC__ >= 4)
/**
 * @brief       This macro provides compiler specific `dllexport` attribute
 *              to deal with shared library functions exportations, only if
 *              supported.
 */
#       define CALC_DLL_EXPORT CALC_ATTRIBUTE(visibility("default"))
#   else
/**
 * @brief       This macro provides compiler specific `dllexport` attribute
 *              to deal with shared library functions exportations, only if
 *              supported.
 */
#       define CALC_DLL_EXPORT
#   endif
#endif

// DLL Attributes

#ifndef CALC_DLL_IMPORT
#   if CALC_PLATFORM_IS_WINDOWS
/**
 * @brief       This macro provides compiler specific `dllimport` attribute
 *              to deal with shared library functions importations, only if
 *              supported.
 */
#       define CALC_DLL_IMPORT CALC_ATTRIBUTE(dllimport)
#   elif (CALC_COMPILER_ID == CALC_COMPILER_ID_GNUC) && (__GNUC__ >= 4)
/**
 * @brief       This macro provides compiler specific `dllimport` attribute
 *              to deal with shared library functions importations, only if
 *              supported.
 */
#       define CALC_DLL_IMPORT CALC_ATTRIBUTE(visibility("default"))
#   else
/**
 * @brief       This macro provides compiler specific `dllimport` attribute
 *              to deal with shared library functions importations, only if
 *              supported.
 */
#       define CALC_DLL_IMPORT
#   endif
#endif

#ifndef CALC_DLL_STATIC
#   if (CALC_COMPILER_ID == CALC_COMPILER_ID_GNUC) && (__GNUC__ >= 4)
/**
 * @brief       This macro makes a function of a shared library be local
 *              in its scope.
 */
#       define CALC_DLL_STATIC CALC_ATTRIBUTE(visibility("hidden"))
#   else
/**
 * @brief       This macro makes a function of a shared library be local
 *              in its scope.
 */
#       define CALC_DLL_STATIC
#   endif
#endif

#pragma endregion

/**
 * @}
 * 
 * @defgroup    C_COMPATIBILITY C Compatibility
 * @{
 */

#pragma region C Compatibility

#ifndef CALC_REGISTER
#   if !defined __cplusplus && (__cplusplus < 201703L)
/**
 * @brief       This constant provides `register` storage modifier. In C,
 *              hints the compiler to store a variable in a processor
 *              `register` instead of default memory for locals.
 *
 * @note        Since C++17, the `register` keyword, is deprecated and out
 *              of support.
 */
#       define CALC_REGISTER register
#   else
/**
 * @brief       This constant provides `register` storage modifier. In C,
 *              hints the compiler to store a variable in a processor
 *              `register` instead of default memory for locals.
 *
 * @note        Since C++17, the `register` keyword, is deprecated and out
 *              of support.
 */
#       define CALC_REGISTER
#   endif
#endif

#ifndef CALC_INLINE
#   if (CALC_C_STANDARD >= CALC_C_STANDARD_C99)
#       if (CALC_COMPILER_ID == CALC_COMPILER_ID_GNUC) || CALC_PLATFORM_IS_UNIX
/**
 * @brief       This constant provides `inline` functions modifier to marks
 *              functions as inlineable. (since C99)
 * 
 * @note        `inline` functions should also be declared as `static` both
 *              in header and source file, so if the `inline` keyword is not
 *              supported, functions denoted by this symbolic constant, are
 *              always `static`. 
 */
#           define CALC_INLINE static inline
#       else
/**
 * @brief       This constant provides `inline` functions modifier to marks
 *              functions as inlineable. (since C99)
 * 
 * @note        `inline` functions should also be declared as `static` both
 *              in header and source file, so if the `inline` keyword is not
 *              supported, functions denoted by this symbolic constant, are
 *              always `static`. 
 */
#           define CALC_INLINE inline
#       endif
#   else
/**
 * @brief       This constant provides `inline` functions modifier to marks
 *              functions as inlineable. (since C99)
 * 
 * @note        `inline` functions should also be declared as `static` both
 *              in header and source file, so if the `inline` keyword is not
 *              supported, functions denoted by this symbolic constant, are
 *              always `static`. 
 */
#       define CALC_INLINE static
#   endif
#endif

#ifndef CALC_EXTERN
/**
 * @brief       This constants marks a function declaration as `extern`,
 *              so declared out of the current scope.
 */
#   define CALC_EXTERN extern
#endif

#ifndef CALC_STATIC
/**
 * @brief       This constants marks a function declaration as `static`,
 *              so visible only in the scope in which is declared.
 */
#   define CALC_STATIC static
#endif

#pragma endregion

/**
 * @}
 */

#ifndef CALC_DEBUG
#   if defined DEBUG || defined _DEBUG
/**
 * @brief       This constant provides an internal debug flag.
 */
#       define CALC_DEBUG 1
#   else
/**
 * @brief       This constant provides an internal debug flag.
 */
#       define CALC_DEBUG 0
#   endif
#endif

#ifndef CALC_BUILD_AS_DLL
#   if (defined DLL || defined _DLL) && CALC_PLATFORM_IS_WINDOWS
/**
 * @brief       This constant provides an internal dll flag.
 */
#       define CALC_BUILD_AS_DLL 1
#   else
/**
 * @brief       This constant provides an internal dll flag.
 */
#       define CALC_BUILD_AS_DLL 0
#   endif
#endif

#endif /* CALC_BASE_DEFS_H_ */
