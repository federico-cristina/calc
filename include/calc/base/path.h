#pragma once

/**
 * @file        path.h
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
 *              to manipulate file paths.
 */

#ifndef CALC_BASE_PATH_H_
#define CALC_BASE_PATH_H_

#include "calc/base/defs.h"

#include <string.h>

#if CALC_PLATFORM_IS_WINDOWS
#   include <direct.h> /* _getcwd, _chdir, ... */

/// @brief Changes the current working directory.
/// @param dirname Path of new working directory.
/// @return These functions return a value of 0 if successful. A
///         return value of -1 indicates failure. If the specified
///         path couldn't be found, errno is set to ENOENT. If
///         dirname is NULL, the invalid parameter handler is invoked,
///         as described in Parameter validation. If execution is
///         allowed to continue, errno is set to EINVAL and the function
///         returns -1.
#   define chdir(dirname)      _chdir((dirname))
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

/// @brief Gets the path's root directory string without checking.
/// @param dest A pointer to the destination buffer in which write
///             the root directory. When NULL the result will be
///             allocated in memory.
/// @param path Source path from which find the result.
/// @return A string containing the path's root directory.
CALC_EXTERN char *CALC_STDCALL path_getroot(char *const dest, const char *const path);
/// @brief Gets the file or directory's name string without checking.
/// @param dest A pointer to the destination buffer in which write
///             the root directory. When NULL the result will be
///             allocated in memory.
/// @param path Source path from which find the result.
/// @return A string containing the path's root directory.
CALC_EXTERN char *CALC_STDCALL path_getname(char *const dest, const char *const path);
/// @brief Gets the file's extension string without checking.
/// @param dest A pointer to the destination buffer in which write
///             the root directory. When NULL the result will be
///             allocated in memory.
/// @param path Source path from which find the result.
/// @return A string containing the path's root directory.
CALC_EXTERN char *CALC_STDCALL path_getextn(char *const dest, const char *const path);
/// @brief Gets the path's base name string without checking.
/// @param dest A pointer to the destination buffer in which write
///             the root directory. When NULL the result will be
///             allocated in memory.
/// @param path Source path from which find the result.
/// @return A string containing the path's root directory.
CALC_EXTERN char *CALC_STDCALL path_getbase(char *const dest, const char *const path);

CALC_C_HEADER_END

#endif // CALC_BASE_PATH_H_
