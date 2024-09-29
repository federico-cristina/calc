#pragma once

/**
 * @file        string.h
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
 *              to allocate, manipulate and operate with strings and
 *              characters.
 */

#ifndef CALC_BASE_STRING_H_
#define CALC_BASE_STRING_H_

#include "calc/base/bool.h"
#include "calc/base/alloc.h"

#include <ctype.h>
#include <string.h>

CALC_C_HEADER_BEGIN

#ifndef NUL
/// @brief This macro represents the string terminator character
///        (NUL).
#   define NUL '\0'
#endif // NUL

/// @brief Checks if the given character is a line termination
///        character.
/// @param c Character to check.
/// @return Non-zero value if the character is a line terminator
///         character, 0 otherwise.
CALC_INLINE int CALC_STDCALL isendln(int c)
{
    return (c == '\r') || (c == '\n') || (c == NUL);
}

/// @brief Checks if the given character is a termination
///        character.
/// @param c Character to check.
/// @return Non-zero value if the character is a line terminator
///         character, 0 otherwise.
CALC_INLINE int CALC_STDCALL istermn(int c)
{
    return (c == NUL) || (c == EOF);
}

#ifndef stralloc
#   if CALC_PLATFORM_IS_WINDOWS
/// @brief Allocates an empty string of a specified number of
///        characters.
/// @param length The number of characters of the string.
/// @return A pointer to the first character of the new allocated
///         string.
#       define stralloc(length) (strset((char *)dim(char, (length) + 1), NUL))
#   else
/// @brief Allocates an empty string of a specified number of
///        characters.
/// @param length The number of characters of the string.
/// @return A pointer to the first character of the new allocated
///         string.
#       define stralloc(length) (memset((char *)dim(char, (length) + 1), NUL, (length) + 1))
#   endif
#endif // stralloc

// String manipulation functions

/// @brief Gets a duplicate of a portion of a string. The name is
///        not strndup to avoid name collisions with strndup(..)
///        extension function.
/// @param str The string to duplicate.
/// @param count The number of characters to duplicate.
/// @return A pointer to the first character of the duplicate
///         string.
CALC_EXTERN char *CALC_CDECL strnget(const char *const str, size_t count);
/// @brief Moves characters from source string into destination
///        buffer. If destination buffer is NULL is allocated a
///        new buffer with as character as specified by count
///        parameter.
/// @param dest Destination buffer.
/// @param src Source string.
/// @param count Number of characters to move.
/// @return A pointer to the destination buffer or to the first
///         character of the new allocated buffer.
CALC_EXTERN char *CALC_CDECL strnmov(char *const dest, const char *const src, size_t count);
/// @brief Converts a source string into its lower-case version
///        and writes the result into a destination buffer or, if
///        that one is NULL, into a new allocated buffer.
/// @param dest Destination buffer.
/// @param src Source string.
/// @param count The number of characters to convert.
/// @return A pointer to the destination buffer or to the first
///         character of the new allocated buffer.
CALC_EXTERN char *CALC_CDECL strnlow(char *const dest, const char *const src, size_t count);
/// @brief Converts a source string into its upper-case version
///        and writes the result into a destination buffer or, if
///        that one is NULL, into a new allocated buffer.
/// @param dest Destination buffer.
/// @param src Source string.
/// @param count The number of characters to convert.
/// @return A pointer to the destination buffer or to the first
///         character of the new allocated buffer.
CALC_EXTERN char *CALC_CDECL strnupp(char *const dest, const char *const src, size_t count);

/// @brief Gets a duplicate of a string. The name is not strdup to
///        avoid name collisions with strdup(..) extension function.
/// @param str String to duplicate.
/// @return A pointer to the first character of the duplicate
///         string.
CALC_INLINE char *CALC_CDECL strget(const char *const str)
{
    CALC_REGISTER char *result;

    if (!str)
        result = stralloc(0);
    else
        result = strnget(str, strlen(str));

    return result;
}

/// @brief Moves characters from source string into destination
///        buffer. If the destination buffer is NULL will be allocated
///        a new buffer.
/// @param dest Destination buffer.
/// @param src Source string.
/// @return A pointer to the destination buffer or to the first
///         character of the new allocated buffer.
CALC_INLINE char *CALC_CDECL strmov(char *const dest, const char *const src)
{
    CALC_REGISTER size_t length;

    if (!src)
        length = 0;
    else
        length = strlen(src);

    return strnmov(dest, src, length);
}

/// @brief Converts a source string into its lower-case version
///        and writes the result into a destination buffer or, if
///        that one is NULL, into a new allocated buffer.
/// @param dest Destination buffer.
/// @param src Source string.
/// @return A pointer to the destination buffer or to the first
///         character of the new allocated buffer.
CALC_INLINE char *CALC_CDECL strlow(char *const dest, const char *const src)
{
    CALC_REGISTER size_t length;

    if (!src)
        length = 0;
    else
        length = strlen(src);

    return strnlow(dest, src, length);
}

/// @brief Converts a source string into its upper-case version
///        and writes the result into a destination buffer or, if
///        that one is NULL, into a new allocated buffer.
/// @param dest Destination buffer.
/// @param src Source string.
/// @return A pointer to the destination buffer or to the first
///         character of the new allocated buffer.
CALC_INLINE char *CALC_CDECL strupp(char *const dest, const char *const src)
{
    CALC_REGISTER size_t length;

    if (!src)
        length = 0;
    else
        length = strlen(src);

    return strnupp(dest, src, length);
}

// String equality functions

/// @brief Compares two strings to check if they're the same or if
///        they have the same content.
/// @param str1 The first string.
/// @param str2 The second string.
/// @return TRUE, if str1 equals to str2. In the other case will be
///         returned FALSE.
CALC_EXTERN bool_t CALC_CDECL streq(const char *const str1, const char *const str2);
/// @brief Compares two strings to check if they're the same or if
///        they have the same content, ignoring the case of characters.
/// @param str1 The first string.
/// @param str2 The second string.
/// @return TRUE, if str1 equals to str2. In the other case will be
///         returned FALSE.
CALC_EXTERN bool_t CALC_CDECL striq(const char *const str1, const char *const str2);

// String array sorting functions

CALC_INLINE int CALC_CDECL _calc_strcmp(const void *const str1, const void *const str2)
{
    return strcmp(*(const char **)str1, *(const char **)str2);
}

CALC_INLINE int CALC_CDECL _calc_stricmp(const void *const str1, const void *const str2)
{
    return stricmp(*(const char **)str1, *(const char **)str2);
}

/// @brief Sorts an array of strings using a specific comparer.
/// @param a The array of strings to sort.
/// @param count The number of items in the array.
/// @param cmp A pointer to the comparer function.
/// @return A pointer to the sorted array.
CALC_INLINE const char **CALC_STDCALL strcsrt(const char **const a, size_t count, int (*cmp)(const void *const, const void *const))
{
    return qsort((void *)a, count, sizeof(*a), cmp), a;
}

/// @brief Sorts a string array using the default comparer.
/// @param a The array of strings to sort.
/// @param count The number of items in the array.
/// @return A pointer to the sorted array.
CALC_INLINE const char **CALC_CDECL strsrt(const char **const a, size_t count)
{
    return strcsrt(a, count, _calc_strcmp);
}

/// @brief Sorts a string array using case insensitive comparer.
/// @param a The array of strings to sort.
/// @param count The number of items in the array.
/// @return A pointer to the sorted array.
CALC_INLINE const char **CALC_CDECL strisrt(const char **const a, size_t count)
{
    return strcsrt(a, count, _calc_stricmp);
}

// String formatting functions

/// @brief Allocates a new formatted string with a va_list,
///        with vprintf-style format.
/// @param format printf-style format string.
/// @param arglist Arguments list.
/// @return A pointer to the new allocated formatted string.
CALC_INLINE char *CALC_CDECL vstrfmt(const char *const format, va_list arglist)
{
    if (!format)
        return NULL;

    int size = vsnprintf(NULL, 0, format, arglist);

    if (!size)
        failno("cannot format an empty string");

    char *result = stralloc(size);

    if (vsprintf(result, format, arglist) != size)
        fail("error: formatted string sizes doesn't match", NULL);

    return result;
}

/// @brief Allocates a new formatted string with a printf-like
///        format.
/// @param format printf-style format string.
/// @param others Arguments list.
/// @return A pointer to the new allocated formatted string.
CALC_INLINE char *CALC_CDECL strfmt(const char *const format, ...)
{
    if (!format)
        return NULL;

    char *result;
    va_list args;

    va_start(args, format);
    result = vstrfmt(format, args);
    va_end(args);

    return result;
}

CALC_C_HEADER_END

#endif // CALC_BASE_STRING_H_
