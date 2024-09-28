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
 *              to manipulate files and paths.
 */

#ifndef CALC_BASE_FILE_H_
#define CALC_BASE_FILE_H_

#include "calc/base/bits.h"
#include "calc/base/string.h"

#if CALC_PLATFORM_IS_WINDOWS
#   include <direct.h> /* _getcwd, _chdir, ... */
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
/// @brief The getcwd() function shall place an absolute pathname
///        of the current working directory in the array pointed
///        to by dest, and return dest. The pathname copied to the
///        array shall contain no components that are symbolic links.
/// @param dest Destination buffer on which copy the current working
///             directory.
/// @param size Is the size in bytes of the character array pointed
///             to by the dest argument. If dest is a null pointer,
///             the behavior of getcwd() is unspecified.
/// @return Upon successful completion, getcwd() shall return the
///         dest argument. Otherwise, getcwd() shall return a NULL
///         pointer and set errno to indicate the error. The contents
///         of the array pointed to by buf are then undefined.
#   define getcwd(dest, size)  _getcwd((dest), (size))

#   ifndef calcIsDirSep
/// @brief Checks if a character is a directory separator.
/// @param c The character to check.
/// @return If c is a directory separator then TRUE, else FALSE.
#       define calcIsDirSep(c)  (c == '/' || c == '\\')
#   endif // calcIsDirSep

#   ifndef calcIsExtSep
/// @brief Checks if a character is an extension separator.
/// @param c The character to check.
/// @return If c is an extension separator then TRUE, else FALSE.
#       define calcIsExtSep(c)  (c == '.')
#   endif // calcIsExtSep

#   ifndef calcIsAbsPath
/// @brief Checks if a string represents an absolute path.
/// @param s The string to check.
/// @return If s is an absolute path then TRUE, else FALSE.
#       define calcIsAbsPath(s) (calcIsDirSep(*s) || (*s && *(s + 1) == ':' && calcIsDirSep(*(s + 2))))
#   endif // calcIsAbsPath

#   ifndef CALC_PATHCMP
/// @brief This macro contains the name of the path comparator
///        function.
#       define CALC_PATHCMP     !stricmp
#   endif // CALC_PATHCMP

#   ifndef CALC_PATHSEP
/// @brief This macro contains the path separator character in a
///        path list.
#       define CALC_PATHSEP     ';'
#   endif // CALC_PATHSEP
#else
#   include <unistd.h>

#   ifndef calcIsDirSep
/// @brief Checks if a character is a directory separator.
/// @param c The character to check.
/// @return If c is a directory separator then TRUE, else FALSE.
#       define calcIsDirSep(c)  (c == '/')
#   endif // calcIsDirSep

#   ifndef calcIsExtSep
/// @brief Checks if a character is an extension separator.
/// @param c The character to check.
/// @return If c is an extension separator then TRUE, else FALSE.
#       define calcIsExtSep(c)  (c == '.')
#   endif // calcIsExtSep

#   ifndef calcIsAbsPath
/// @brief Checks if a string represents an absolute path.
/// @param s The string to check.
/// @return If s is an absolute path then TRUE, else FALSE.
#       define calcIsAbsPath(s) calcIsDirSep(*s)
#   endif // calcIsAbsPath

#   ifndef CALC_PATHCMP
/// @brief This macro contains the name of the path comparator
///        function.
#       define CALC_PATHCMP     !strcmp
#   endif // CALC_PATHCMP

#   ifndef CALC_PATHSEP
/// @brief This macro contains the path separator character in a
///        path list.
#       define CALC_PATHSEP     ':'
#   endif // CALC_PATHSEP
#endif

CALC_C_HEADER_BEGIN

/// @brief Checks the existance of a file.
/// @param path A path to a file.
/// @return TRUE if the file exists, otherwise FALSE.
CALC_INLINE bool_t CALC_STDCALL fexists(const char *const path)
{
    return (bool_t)!access(path, F_OK);
}

/// @brief Gets the base name without an extension of a file.
/// @param path Path from which scan the name.
/// @param dest Buffer on which write the name.
/// @return On success a pointer to dest, else NULL.
CALC_EXTERN char *CALC_STDCALL fgetbase(char *const dest, const char *const path);

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
