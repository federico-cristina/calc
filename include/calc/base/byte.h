#pragma once

/**
 * @file        byte.h
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
 * @brief       In this header is defined byte_t datatype with its limits
 *              and functions to manipulate, check and convert buffer of
 *              bytes.
 */

#ifndef CALC_BASE_BYTE_H_
#define CALC_BASE_BYTE_H_

#include "calc/base/bool.h"
#include "calc/base/utils.h"

#include <assert.h>

CALC_C_HEADER_BEGIN

/**
 * @brief       Byte data type. byte_t is ment to store a single byte of memory
 *              (the smallest addressable unit of addressable memory.
 */
typedef unsigned char byte_t;

#ifndef BYTE_MIN
/**
 * @brief       This macro represents the minimum value that a byte_t can store.
 */
#   define BYTE_MIN ((byte_t)0x00)
#endif

#ifndef BYTE_MAX
/**
 * @brief       This macro represents the maximum value that a byte_t can store.
 */
#   define BYTE_MAX ((byte_t)0xFF)
#endif

/**
 * @defgroup    BUFFER_MANIPULATION_FUNCTIONS Buffer Manipulation Functions
 * @{
 */

#pragma region Buffer Manipulation Functions

/**
 * @brief       Sets all bytes of a destination buffer to a given value.
 * 
 * @param       buf A pointer to the buffer to set.
 * @param       value The value to set to each byte of the buffer.
 * @param       count Number of bytes to set.
 * @return      In case of success this function returns a pointer to the input
 *              buffer.
 */
CALC_INLINE byte_t *CALC_STDCALL bufset(byte_t *const buf, byte_t value, size_t count)
{
    if (!count)
        return buf;

    assert(buf != NULL);

    CALC_REGISTER size_t i;

    for (i = 0; i < count; i++)
        buf[i] = value;

    return buf;
}

/**
 * @brief       Sets all bytes of a destination buffer to the minimun value (zero).
 * 
 * @param       buf         A pointer to the buffer to clear.
 * @param       count       Number of bytes in the buffer.
 * @return      In case of success this function returns a pointer to the input
 *              buffer.
 */
CALC_INLINE byte_t *CALC_STDCALL bufclr(byte_t *const buf, size_t count)
{
    return bufset(buf, BYTE_MIN, count);
}

/**
 * @brief       Copies the content from a source constant buffer to a destination
 *              buffer.
 *              
 * @param       dest A pointer to the destination buffer.
 * @param       source A pointer to the source buffer.
 * @param       count Number of bytes to copy.
 * @return      In case of success this function returns a pointer to the destination
 *              buffer.
 */
CALC_INLINE byte_t *CALC_STDCALL bufcpy(byte_t *const dest, const byte_t *const source, size_t count)
{
    assert((dest != NULL) && (source != NULL));

    CALC_REGISTER size_t i;

    for (i = 0; i < count; i++)
        dest[i] = source[i];

    return dest;
}

/**
 * @brief       Moves the content from a source constant buffer to a destination
 *              buffer.
 * 
 * @param       dest A pointer to the destination buffer.
 * @param       source A pointer to the source buffer.
 * @param       count Number of bytes to copy.
 * @return      In case of success this function returns a pointer to the destination
 *              buffer.
 */
CALC_INLINE byte_t *CALC_STDCALL bufmov(byte_t *const dest, byte_t *const source, size_t count)
{
    assert((dest != NULL) && (source != NULL));

    CALC_REGISTER size_t i;

    for (i = 0; i < count; i++)
        dest[i] = source[i], source[i] = BYTE_MIN;

    return dest;
}

/**
 * @brief       Swaps the content of two buffers.
 * 
 * @param       buf1 A pointer to the first buffer.
 * @param       buf2 A pointer to the second buffer.
 * @param       count Number of bytes to swap.
 * @return      On success returns buf1.
 */
CALC_INLINE byte_t *CALC_STDCALL bufswp(byte_t *const buf1, byte_t *const buf2, size_t count)
{
    assert((buf1 != NULL) && (buf2 != NULL));

    CALC_REGISTER size_t i;
    CALC_REGISTER byte_t bTemp;

    for (i = 0; i < count; i++)
    {
        bTemp = buf1[i];
        buf1[i] = buf2[i];
        buf2[i] = bTemp;
    }

    return buf1;
}

/**
 * @brief       Revertes the content of a source constant buffer to a destination
 *              buffer.
 * 
 * @param       dest A pointer to the destination buffer.
 * @param       source A pointer to the source buffer.
 * @param       count Number of bytes to copy.
 * @return      In case of success this function returns a pointer to the destination
 *              buffer.
 */
CALC_INLINE byte_t *CALC_STDCALL bufrev(byte_t *const dest, const byte_t *const source, size_t count)
{
    assert((dest != NULL) && (source != NULL));

    CALC_REGISTER size_t i;

    for (i = 0; i < count; i++)
        dest[i] = source[count - i - 1];

    return dest;
}

#pragma endregion

/**
 * @}
 * 
 * @defgroup    BUFFER_CHECKING_FUNCTIONS Buffer Checking Functions
 * @{
 */

#pragma region Buffer Checking Functions

/**
 * @brief       Compares a portion two buffers to check if they've the same
 *              content.
 * 
 * @param       buf1 A pointer to the first buffer.
 * @param       buf2 A pointer to the second buffer.
 * @param       count Number of bytes to copy.
 * @return      In case of success this function returns TRUE, else FALSE.
 */
CALC_INLINE bool_t CALC_STDCALL bufcmp(const byte_t *const buf1, const byte_t *const buf2, size_t count)
{
    assert((buf1 != NULL) && (buf2 != NULL));

    CALC_REGISTER size_t i;
    CALC_REGISTER bool_t r = TRUE;

    for (i = 0; r && (i < count); i++)
        r = (buf1[i] == buf2[i]);

    return r;
}

/**
 * @brief       Checks if a portion of a given buffer content has only zeros.
 * 
 * @param       buf A pointer to the buffer to check.
 * @param       count Number of bytes to copy.
 * @return      In case of success this function returns TRUE, else FALSE.
 */
CALC_INLINE bool_t CALC_STDCALL bufnil(const byte_t *const buf, size_t count)
{
    assert(buf != NULL);

    CALC_REGISTER size_t i;
    CALC_REGISTER bool_t r = TRUE;

    for (i = 0; r && (i < count); i++)
        r = !((int)buf[i]);

    return r;
}

/**
 * @brief       This function counts the number of bytes before a specific
 *              terminator byte.
 * 
 * @param       buf A pointer to buffer to count.
 * @param       term The terminator byte.
 * @return      The number of bytes before the terminator byte. 
 */
CALC_INLINE size_t CALC_STDCALL bufcnt(const byte_t *const buf, byte_t term)
{
    assert(buf != NULL);

    CALC_REGISTER size_t i = 0;

    while (buf[i] != term)
        ++i;

    return i;
}

/**
 * @brief       This function counts the number of bytes before the first
 *              `BYTE_MIN`.
 * 
 * @param       buf A pointer to buffer to count.
 * @return      The number of bytes before the `BYTE_MIN` byte. 
 */
CALC_INLINE size_t CALC_STDCALL buflen(const byte_t *const buf)
{
    return bufcnt(buf, BYTE_MIN);
}

#pragma endregion

/**
 * @}
 * 
 * @defgroup    BUFFER_CONVERSION_FUNCTIONS Buffer Conversion Functions
 * @{
 */

#pragma region Buffer Conversion Functions

#ifndef tobuf
/**
 * @brief       Copies a value into a buffer.
 * 
 * @warning     This operation is very unsafe.
 * 
 * @param       dest A pointer to the destination buffer.
 * @param       val The value from which copy.
 * @param       count Number of bytes to copy in the destination.
 * @return      In case of success this function returns a pointer to the destination
 *              buffer.
 */
#   define tobuf(dest, val, count) bufcpy((dest), (byte_t *)&(val), min((count), sizeof(val)))
#endif

/**
 * @brief       This function copies the bytes representation of unsigned integer
 *              into a destination buffer.
 * 
 * @param       dest A pointer to the destination buffer.
 * @param       val The value from which copy.
 * @param       count Number of bytes to copy in the destination.
 * @return      In case of success this function returns a pointer to the destination
 *              buffer.
 */
CALC_INLINE byte_t *CALC_STDCALL utobuf(byte_t *const dest, unsigned int val, size_t count)
{
    return tobuf(dest, val, count);
}

/**
 * @brief       This function copies the bytes representation of unsigned long integer
 *              into a destination buffer.
 * 
 * @param       dest A pointer to the destination buffer.
 * @param       val The value from which copy.
 * @param       count Number of bytes to copy in the destination.
 * @return      In case of success this function returns a pointer to the destination
 *              buffer.
 */
CALC_INLINE byte_t *CALC_STDCALL ultobuf(byte_t *const dest, unsigned long val, size_t count)
{
    return tobuf(dest, val, count);
}

/**
 * @brief       This function copies the bytes representation of unsigned long long
 *              integer into a destination buffer.
 * 
 * @param       dest A pointer to the destination buffer.
 * @param       val The value from which copy.
 * @param       count Number of bytes to copy in the destination.
 * @return      In case of success this function returns a pointer to the destination
 *              buffer.
 */
CALC_INLINE byte_t *CALC_STDCALL ulltobuf(byte_t *const dest, unsigned long long val, size_t count)
{
    return tobuf(dest, val, count);
}

/**
 * @brief       This function copies the bytes representation of signed integer
 *              into a destination buffer.
 * 
 * @param       dest A pointer to the destination buffer.
 * @param       val The value from which copy.
 * @param       count Number of bytes to copy in the destination.
 * @return      In case of success this function returns a pointer to the destination
 *              buffer.
 */
CALC_INLINE byte_t *CALC_STDCALL itobuf(byte_t *const dest, int val, size_t count)
{
    return tobuf(dest, val, count);
}

/**
 * @brief       This function copies the bytes representation of signed long integer
 *              into a destination buffer.
 * 
 * @param       dest A pointer to the destination buffer.
 * @param       val The value from which copy.
 * @param       count Number of bytes to copy in the destination.
 * @return      In case of success this function returns a pointer to the destination
 *              buffer.
 */
CALC_INLINE byte_t *CALC_STDCALL ltobuf(byte_t *const dest, long val, size_t count)
{
    return tobuf(dest, val, count);
}

/**
 * @brief       This function copies the bytes representation of signed long long
 *              integer into a destination buffer.
 * 
 * @param       dest A pointer to the destination buffer.
 * @param       val The value from which copy.
 * @param       count Number of bytes to copy in the destination.
 * @return      In case of success this function returns a pointer to the destination
 *              buffer.
 */
CALC_INLINE byte_t *CALC_STDCALL lltobuf(byte_t *const dest, long long val, size_t count)
{
    return tobuf(dest, val, count);
}

/**
 * @brief       This function copies the bytes representation of float into a
 *              destination buffer.
 * 
 * @param       dest A pointer to the destination buffer.
 * @param       val The value from which copy.
 * @param       count Number of bytes to copy in the destination.
 * @return      In case of success this function returns a pointer to the destination
 *              buffer.
 */
CALC_INLINE byte_t *CALC_STDCALL ftobuf(byte_t *const dest, float val, size_t count)
{
    return tobuf(dest, val, count);
}

/**
 * @brief       This function copies the bytes representation of double into a
 *              destination buffer.
 * 
 * @param       dest A pointer to the destination buffer.
 * @param       val The value from which copy.
 * @param       count Number of bytes to copy in the destination.
 * @return      In case of success this function returns a pointer to the destination
 *              buffer.
 */
CALC_INLINE byte_t *CALC_STDCALL dtobuf(byte_t *const dest, double val, size_t count)
{
    return tobuf(dest, val, count);
}

/**
 * @brief       This function copies the bytes representation of long double
 *              into a destination buffer.
 * 
 * @param       dest A pointer to the destination buffer.
 * @param       val The value from which copy.
 * @param       count Number of bytes to copy in the destination.
 * @return      In case of success this function returns a pointer to the destination
 *              buffer.
 */
CALC_INLINE byte_t *CALC_STDCALL ldtobuf(byte_t *const dest, long double val, size_t count)
{
    return tobuf(dest, val, count);
}

#ifndef bufto
/**
 * @brief       Copies a sequence of bytes into a destination variable. 
 * 
 * @warning     This operation is very unsafe.
 * 
 * @param       dest Destination variable in which copy the value.
 * @param       source Source buffer form which copy the value.
 * @param       count Number of bytes to copy in the destination.
 * @return      A copy of the destination value.
 */
#   define bufto(dest, source, count) bufcpy((byte_t *)&(dest), (source), min((count), sizeof(dest)));
#endif

/**
 * @brief       Copies a sequence of bytes into an unsigned integer destination
 *              variable. 
 * 
 * @param       buf A pointer to the source buffer.
 * @param       count Number of bytes to copy.
 * @return      The numeric value. 
 */
CALC_INLINE unsigned int CALC_STDCALL buftou(const byte_t *const buf, size_t count)
{
    unsigned int tmp = 0;
    bufto(tmp, buf, count);
    return tmp;
}

/**
 * @brief       Copies a sequence of bytes into an unsigned long integer destination
 *              variable. 
 * 
 * @param       buf A pointer to the source buffer.
 * @param       count Number of bytes to copy.
 * @return      The numeric value. 
 */
CALC_INLINE unsigned long CALC_STDCALL buftoul(const byte_t *const buf, size_t count)
{
    unsigned long tmp = 0;
    bufto(tmp, buf, count);
    return tmp;
}

/**
 * @brief       Copies a sequence of bytes into an unsigned long long integer
 *              destination variable. 
 * 
 * @param       buf A pointer to the source buffer.
 * @param       count Number of bytes to copy.
 * @return      The numeric value. 
 */
CALC_INLINE unsigned long long CALC_STDCALL buftoull(const byte_t *const buf, size_t count)
{
    unsigned long long tmp = 0;
    bufto(tmp, buf, count);
    return tmp;
}

/**
 * @brief       Copies a sequence of bytes into an signed integer destination
 *              variable. 
 * 
 * @param       buf A pointer to the source buffer.
 * @param       count Number of bytes to copy.
 * @return      The numeric value. 
 */
CALC_INLINE int CALC_STDCALL buftoi(const byte_t *const buf, size_t count)
{
    int tmp = 0;
    bufto(tmp, buf, count);
    return tmp;
}

/**
 * @brief       Copies a sequence of bytes into an signed long integer destination
 *              variable. 
 * 
 * @param       buf A pointer to the source buffer.
 * @param       count Number of bytes to copy.
 * @return      The numeric value. 
 */
CALC_INLINE long CALC_STDCALL buftol(const byte_t *const buf, size_t count)
{
    long tmp = 0;
    bufto(tmp, buf, count);
    return tmp;
}

/**
 * @brief       Copies a sequence of bytes into an signed long long integer
 *              destination variable. 
 * 
 * @param       buf A pointer to the source buffer.
 * @param       count Number of bytes to copy.
 * @return      The numeric value. 
 */
CALC_INLINE long long CALC_STDCALL buftoll(const byte_t *const buf, size_t count)
{
    long long tmp = 0;
    bufto(tmp, buf, count);
    return tmp;
}

/**
 * @brief       Copies a sequence of bytes into an float destination
 *              variable. 
 * 
 * @param       buf A pointer to the source buffer.
 * @param       count Number of bytes to copy.
 * @return      The numeric value. 
 */
CALC_INLINE float CALC_STDCALL buftof(const byte_t *const buf, size_t count)
{
    float tmp = 0;
    bufto(tmp, buf, count);
    return tmp;
}

/**
 * @brief       Copies a sequence of bytes into an double destination
 *              variable. 
 * 
 * @param       buf A pointer to the source buffer.
 * @param       count Number of bytes to copy.
 * @return      The numeric value. 
 */
CALC_INLINE double CALC_STDCALL buftod(const byte_t *const buf, size_t count)
{
    double tmp = 0;
    bufto(tmp, buf, count);
    return tmp;
}

/**
 * @brief       Copies a sequence of bytes into an long double destination
 *              variable. 
 * 
 * @param       buf A pointer to the source buffer.
 * @param       count Number of bytes to copy.
 * @return      The numeric value. 
 */
CALC_INLINE long double CALC_STDCALL buftold(const byte_t *const buf, size_t count)
{
    long double tmp = 0;
    bufto(tmp, buf, count);
    return tmp;
}

#pragma endregion

/**
 * @}
 */

CALC_C_HEADER_END

#endif // CALC_BASE_BYTE_H_
