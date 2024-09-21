#pragma once

/**
 * @file        errno.h
 * 
 * @author      Federico Cristina <federico.cristina@outlook.it>
 * 
 * @copyright   Copyright (c) 2024 Federico Cristina
 *              
 *              This file is part of the calc scripting language project,
 *              under the Apache License v2.0. See LICENSE for license
 *              informations.
 * 
 * @brief       In this header are defined functions to print on the
 *              standard error stream and functions to handle errno
 *              names and messages.
 */

#ifndef CALC_BASE_ERRNO_H_
#define CALC_BASE_ERRNO_H_

#include "calc/base/defs.h"

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#pragma warning(disable: 4311)
#pragma warning(disable: 4996)

CALC_C_HEADER_BEGIN

// stderr print functions

/// @brief This function prints an error message on the standard error
///        stream.
/// @param format Pointer to a null-terminated byte string specifying
///               how to interpret the data.
/// @param arglist Variable argument list containing the data to print.
/// @return The number of characters written if successful or negative
///         value if an error occurred.
CALC_INLINE int CALC_STDCALL veprintf(const char *const format, va_list arglist)
{
    return vfprintf(stderr, format, arglist);
}

/// @brief This function prints an error message on the standard error
///        stream.
/// @param format Pointer to a null-terminated byte string specifying
///               how to interpret the data.
/// @param others Variable argument list containing the data to print.
/// @return The number of characters written if successful or negative
///         value if an error occurred.
CALC_INLINE int CALC_CDECL eprintf(const char *const format, ...)
{
    int result;
    va_list args;

    va_start(args, format);
    result = veprintf(format, args);
    va_end(args);

    return result;
}

/// @brief This function prints an error message on the standard error
///        stream with a line terminator at the end.
/// @param format Pointer to a null-terminated byte string specifying
///               how to interpret the data.
/// @param arglist Variable argument list containing the data to print.
/// @return The number of characters written if successful or negative
///         value if an error occurred.
CALC_INLINE int CALC_STDCALL veprintfn(const char *const format, va_list arglist)
{
    int result = 0;

    result += vfprintf(stderr, format, arglist);
    result += fputs("\n", stderr);

    return result;
}

/// @brief This function prints an error message on the standard error
///        stream with a line terminator at the end.
/// @param format Pointer to a null-terminated byte string specifying
///               how to interpret the data.
/// @param others Variable argument list containing the data to print.
/// @return The number of characters written if successful or negative
///         value if an error occurred.
CALC_INLINE int CALC_CDECL eprintfn(const char *const format, ...)
{
    int result;
    va_list args;

    va_start(args, format);
    result = veprintfn(format, args);
    va_end(args);

    return result;
}

// errno handling functions

/// @brief This function provides maps each errno code to its name (or
///        associated macro name).
/// 
///        The source code of this function has been imported from an
///        external source. Repository address:
/// 
///        https://github.com/mentalisttraceur/errnoname.git
/// 
/// @param no Errno code.
/// @return A pointer to the constant string containing the name of the
///         errno.
CALC_EXTERN const char *CALC_STDCALL errnoname(int no);

/// @brief This function prints on the error stream a message in which is
///        displayed the errno and its message. (This function has been
///        created to be used with atexit(...) function)
CALC_INLINE void CALC_STDCALL perrno(void)
{
    if (errno)
        eprintfn("errno %d (%s): %s", errno, errnoname(errno), strerror(errno));

    return;
}

CALC_C_HEADER_END

#endif // CALC_BASE_ERRNO_H_
