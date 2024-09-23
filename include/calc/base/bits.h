#pragma once

/**
 * @file        bits.h
 * 
 * @author      Federico Cristina <federico.cristina@outlook.it>
 * 
 * @copyright   Copyright (c) 2024 Federico Cristina
 *              
 *              This file is part of the calc scripting language project,
 *              under the Apache License v2.0. See LICENSE for license
 *              informations.
 * 
 * @brief       In this header are defined utility macros and constants
 *              to work with type sizes. In this header are also defined
 *              fixed bit width datatypes.
 */

#ifndef CALC_BASE_BITS_H_
#define CALC_BASE_BITS_H_

#include "calc/base/defs.h"

#include <float.h>
#include <limits.h>

#ifndef countof
/// @brief Computes the number of elements in a specified
///        array.
/// 
///        NOTE: This macro works only if used with arrays
///        and NOT with pointer NOR pointers to an array.
/// 
/// @param array The array which is requested the length. 
/// @returns The number of elements in the array.
#   define countof(array) (sizeof(array) / sizeof(*array))
#endif // countof

#ifndef CALC_BITSOF_CHAR
/// @brief This macro holds the number of bits in a system char
///        to compute the number of bits in other data types.
#   define CALC_BITSOF_CHAR CHAR_BIT
#endif // CALC_BITSOF_CHAR

#ifndef CALC_BITSOF_WORD
/// @brief This macro holds the number of bits in a system word
///        to compute the number of words in other data types.
#   define CALC_BITSOF_WORD (CALC_BITSOF_CHAR * sizeof(int))
#endif // CALC_BITSOF_WORD

#ifndef CALC_BITSOF_WORD_PTR
/// @brief This macro holds the number of bits in a system word
///        pointer.
#   define CALC_BITSOF_WORD_PTR (CALC_BITSOF_CHAR * sizeof(int*))
#endif // CALC_BITSOF_WORD_PTR

#ifndef bitsof
/// @brief Computes the number of bits in a specified data type.
/// @param T Specified data type.
/// @return The number of bits required from a value of type T.
#   define bitsof(T)   ((size_t)(sizeof(T) * CALC_BITSOF_CHAR))
#endif // bitsof

#ifndef wordsin
/// @brief Computes the number of words in a specified data type.
/// @param T Specified data type.
/// @return The number of words required from a value of type T.
///         If the type is smaller than a word, this macro returns
///         zero. (To get a real value use ldwordsin)
#   define wordsin(T)  ((size_t)(bitsof(T) / CALC_BITSOF_WORD))
#endif // wordsin

#ifndef ldwordsin
/// @brief Computes the number of words in a specified data type.
/// @param T Specified data type.
/// @return The number of words required from a value of type T.
#   define ldwordsin(T) ((long double)bitsof(T) / (long double)CALC_BITSOF_WORD)
#endif // ldwordsin

#ifndef CALC_PAGESIZ
/// @brief This macro holds a constant value to use as constant,
///        the value is common on many systems.
#   define CALC_PAGESIZ 4096
#endif // CALC_PAGESIZ

CALC_C_HEADER_BEGIN

#if !defined CALC_USE_STDINT

// Signed integers

/// @brief Signed 8-bit integer datatype.
typedef signed char int8_t;

#ifndef INT8_MIN
/// @brief This macro represents the minimum value representable
///        with an 8-bit signed integer.
#   define INT8_MIN ((int8_t)(-0x80))
#endif // INT8_MIN

#ifndef INT8_MAX
/// @brief This macro represents the maximum value representable
///        with an 8-bit signed integer.
#   define INT8_MAX ((int8_t)(+0x7F))
#endif // INT8_MAX

/// @brief Signed 16-bit integer datatype.
typedef short int16_t;

#ifndef INT16_MIN
/// @brief This macro represents the minimum value representable
///        with an 16-bit signed integer.
#   define INT16_MIN ((int16_t)(-0x8000))
#endif // INT16_MIN

#ifndef INT16_MAX
/// @brief This macro represents the maximum value representable
///        with an 16-bit signed integer.
#   define INT16_MAX ((int16_t)(+0x7FFF))
#endif // INT16_MAX

/// @brief Signed 32-bit integer datatype.
typedef int int32_t;

#ifndef INT32_MIN
/// @brief This macro represents the minimum value representable
///        with an 32-bit signed integer.
#   define INT32_MIN ((int32_t)(-0x80000000))
#endif // INT32_MIN

#ifndef INT32_MAX
/// @brief This macro represents the maximum value representable
///        with an 32-bit signed integer.
#   define INT32_MAX ((int32_t)(+0x7FFFFFFF))
#endif // INT32_MAX

/// @brief Signed 64-bit integer datatype.
typedef long long int64_t;

#ifndef INT64_MIN
/// @brief This macro represents the minimum value representable
///        with an 64-bit signed integer.
#   define INT64_MIN ((int64_t)(-0x8000000000000000))
#endif // INT64_MIN

#ifndef INT64_MAX
/// @brief This macro represents the maximum value representable
///        with an 64-bit signed integer.
#   define INT64_MAX ((int64_t)(+0x7FFFFFFFFFFFFFFF))
#endif // INT64_MAX

// Unsigned integers

/// @brief Unsigned 8-bit integer datatype.
typedef unsigned char uint8_t;

#ifndef UINT8_MIN
/// @brief This macro represents the minimum value representable
///        with an 8-bit unsigned integer.
#   define UINT8_MIN ((uint8_t)(0x00U))
#endif // UINT8_MIN

#ifndef UINT8_MAX
/// @brief This macro represents the maximum value representable
///        with an 8-bit unsigned integer.
#   define UINT8_MAX ((uint8_t)(0xFFU))
#endif // UINT8_MAX

/// @brief Unsigned 16-bit integer datatype.
typedef unsigned short uint16_t;

#ifndef UINT16_MIN
/// @brief This macro represents the minimum value representable
///        with an 16-bit unsigned integer.
#   define UINT16_MIN ((uint16_t)(0x0000U))
#endif // UINT16_MIN

#ifndef UINT16_MAX
/// @brief This macro represents the maximum value representable
///        with an 16-bit unsigned integer.
#   define UINT16_MAX ((uint16_t)(0xFFFFU))
#endif // UINT16_MAX

/// @brief Unsigned 32-bit integer datatype.
typedef unsigned int uint32_t;

#ifndef UINT32_MIN
/// @brief This macro represents the minimum value representable
///        with an 32-bit unsigned integer.
#   define UINT32_MIN ((uint32_t)(0x00000000U))
#endif // UINT32_MIN

#ifndef UINT32_MAX
/// @brief This macro represents the maximum value representable
///        with an 32-bit unsigned integer.
#   define UINT32_MAX ((uint32_t)(0xFFFFFFFFU))
#endif // UINT32_MAX

/// @brief Unsigned 64-bit integer datatype.
typedef unsigned long long uint64_t;

#ifndef UINT64_MIN
/// @brief This macro represents the minimum value representable
///        with an 64-bit unsigned integer.
#   define UINT64_MIN ((uint64_t)(0x0000000000000000U))
#endif // UINT64_MIN

#ifndef UINT64_MAX
/// @brief This macro represents the maximum value representable
///        with an 64-bit unsigned integer.
#   define UINT64_MAX ((uint64_t)(0xFFFFFFFFFFFFFFFFU))
#endif // UINT64_MAX

#else
#   include <stdint.h>
#endif

#if CALC_PLATFORM_IS_WINDOWS && !defined SSIZE_T

#ifndef SSIZE_T
/// @brief Signed size type macro.
#   define SSIZE_T long long
#endif // SSIZE_T

/// @brief Signed sise datatype.
typedef SSIZE_T ssize_t;

#ifndef SSIZE_MIN
/// @brief This macro represents the minimum ssize_t value.
#   define SSIZE_MIN ((ssize_t)LLONG_MIN)
#endif // SSIZE_MIN

#ifndef SSIZE_MAX
/// @brief This macro represents the maximum ssize_t value.
#   define SSIZE_MAX ((ssize_t)LLONG_MAX)
#endif // SSIZE_MAX

#endif

CALC_C_HEADER_END

#endif // CALC_BASE_BITS_H_
