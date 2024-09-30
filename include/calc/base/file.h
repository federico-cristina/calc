#pragma once

/**
 * @file        file.h
 *
 * @author      Federico Cristina <federico.cristina@outlook.it>
 *
 * @copyright   Copyright (c) 2024 Federico Cristina
 *
 *              This file is part of the calc scripting language project,
 *              under the Apache License v2.0. See LICENSE for license
 *              informations.
 *
 * @brief       In this header are defined macros, constants and functions
 *              to manipulate files.
 */

#ifndef CALC_BASE_FILE_H_
#define CALC_BASE_FILE_H_

#include "calc/base/bool.h"
#include "calc/base/string.h"

#include <stdio.h>

#if CALC_PLATFORM_IS_WINDOWS
#   include <io.h>     /* open, creat, remove, ... */
#   include <fcntl.h>

#   ifndef F_OK

CALC_C_HEADER_BEGIN

/// @brief Enumerates the access modes, to use in access(...)
///        function.
typedef enum _AccessMode
{
    /// @brief Existance only check.
    F_OK = 0x00,
    /// @brief Write permission check.
    W_OK = 0x02,
    /// @brief Read permission check.
    R_OK = 0x04,
    /// @brief Both read and write permissions check.
    X_OK = W_OK | R_OK,
} amode_t;

CALC_C_HEADER_END

#   endif

/// @brief The access() function shall check the file named
///        by the pathname pointed to by the path argument
///        for accessibility according to the bit pattern
///        contained in mode, using the real user ID in place
///        of the effective user ID and the real group ID in
///        place of the effective group ID.
/// @param path Path of the file to check.
/// @param mode The value of amode is either the bitwise-inclusive
///             OR of the access permissions to be checked (R_OK,
///             W_OK, X_OK) or the existence test (F_OK).
/// @return If the requested access is permitted, access() succeeds
///         and shall return 0; otherwise, -1 shall be returned
///         and errno shall be set to indicate the error.
#   define access(path, mode)  _access((path), (mode))
#else
#   include <unistd.h>
#endif

CALC_C_HEADER_BEGIN

/// @brief Checks the existance of a file.
/// @param path A path to a file.
/// @return TRUE if the file exists, otherwise FALSE.
CALC_INLINE bool_t CALC_STDCALL fexists(const char *const path)
{
    return (bool_t)!access(path, F_OK);
}

#ifndef EOF
/// @brief This macro represents the end of file character.
///
///        NOTE: Normally this macro should be defined in stdio.h,
///        if is redefined here, maybe there's something that don't
///        work...
///
#   define EOF (-1)
#endif // EOF

#ifndef EOL
/// @brief This macro represents the end of line character (LF).
#   define EOL '\n'
#endif // EOL

#ifndef NUL
/// @brief This macro represents the string terminator character
///        (NUL).
#   define NUL '\0'
#endif // NUL

#ifndef TAB
/// @brief This macro represents the horizontal tabulation
///        character (HTB).
#   define TAB '\t'
#endif // TAB

#ifndef CALC_LOADMOD
#   if CALC_PLATFORM_IS_WINDOWS
/// @brief This macro represents the default mode to apply to a
///        file if the intention is to load its content. On
///        Windows systems (that uses CRLF line endings) the
///        read mode doesn't work properly, so it's necessary
///        read the file as a binary stream.
#       define CALC_LOADMOD "rb"
#   else
/// @brief This macro represents the default mode to apply to a
///        file if the intention is to load its content.
#       define CALC_LOADMOD "r"
#   endif
#endif // CALC_LOADMOD

/// @brief This function computes the size of a file (in bytes).
/// @param stream The file stream to use as source to compute
///               the size.
/// @return The size, in bytes, of the specified file stream.
CALC_EXTERN size_t CALC_STDCALL fgetsiz(FILE *const stream);

CALC_C_HEADER_END

#endif // CALC_BASE_FILE_H_
