#pragma once

/**
 * @file        byte.h
 *
 * @author      Federico Cristina <federico.cristina@outlook.it>
 *
 * @copyright   Copyright (c) 2024 Federico Cristina
 *
 *              This file is part of the calc scripting language project,
 *              under the Apache License v2.0. See LICENSE for license
 *              informations.
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

/// @brief Byte data type. byte_t is ment to store a single
///        byte of memory (the smallest addressable unit of
///        memory.
typedef unsigned char byte_t;

#ifndef BYTE_MIN
/// @brief This macro represents the minimum value that a
///        variable of type byte_t can store.
#	define BYTE_MIN ((byte_t)0x00)
#endif // BYTE_MIN

#ifndef BYTE_MAX
/// @brief This macro represents the maximum value that a
///        variable of type byte_t can store.
#	define BYTE_MAX ((byte_t)0xFF)
#endif // BYTE_MAX

// Buffer Manipulation Functions

/// @brief Sets all bytes of a destination buffer to a given
///        value.
/// @param dest Destination buffer pointer.
/// @param value Source buffer pointer.
/// @param count The number of bytes to set.
/// @return In case of success this function returns a pointer
///         to the destination buffer.
CALC_INLINE byte_t *CALC_STDCALL bufset(byte_t *const dest, byte_t value, size_t count)
{
	if (!count)
		return dest;

	assert(dest != NULL);

	CALC_REGISTER size_t i;

	for (i = 0; i < count; i++)
		dest[i] = value;

	return dest;
}

/// @brief Sets all bytes of a destination buffer to the minimun
///        value (zero).
/// @param dest Destination buffer pointer.
/// @param count The number of bytes to set.
/// @return In case of success this function returns a pointer
///         to the destination buffer.
CALC_INLINE byte_t *CALC_STDCALL bufclr(byte_t *const dest, size_t count)
{
	return bufset(dest, BYTE_MIN, count);
}

/// @brief Copies the content from a source constant buffer
///        to a destination buffer.
/// @param dest Destination buffer pointer.
/// @param source Source buffer pointer.
/// @param count The number of bytes to copy.
/// @return In case of success this function returns a pointer
///         to the destination buffer.
CALC_INLINE byte_t *CALC_STDCALL bufcpy(byte_t *const dest, const byte_t *const source, size_t count)
{
	assert((dest != NULL) && (source != NULL));

	CALC_REGISTER size_t i;

	for (i = 0; i < count; i++)
		dest[i] = source[i];

	return dest;
}

/// @brief Moves the content from a source constant buffer
///        to a destination buffer.
/// @param dest Destination buffer pointer.
/// @param source Source buffer pointer.
/// @param count The number of bytes to move.
/// @return In case of success this function returns a pointer
///         to the destination buffer.
CALC_INLINE byte_t *CALC_STDCALL bufmov(byte_t *const dest, byte_t *const source, size_t count)
{
	assert((dest != NULL) && (source != NULL));

	CALC_REGISTER size_t i;

	for (i = 0; i < count; i++)
		dest[i] = source[i], source[i] = BYTE_MIN;

	return dest;
}

/// @brief Swaps the content of two buffers.
/// @param b1 The first buffer.
/// @param b2 The second buffer;
/// @param count The number of bytes to swap.
/// @return On success returns b1.
CALC_INLINE byte_t *CALC_STDCALL bufswp(byte_t *const b1, byte_t *const b2, size_t count)
{
	assert((b1 != NULL) && (b2 != NULL));

	CALC_REGISTER size_t i;
	CALC_REGISTER byte_t bTemp;

	for (i = 0; i < count; i++)
	{
		bTemp = b1[i];
		b1[i] = b2[i];
		b2[i] = bTemp;
	}

	return b1;
}

// Buffer Checking Functions

/// @brief Compares a portion two buffers to check if they've
///        the same content.
/// @param b1 First buffer.
/// @param b2 Second buffer.
/// @param count The number of bytes to compare.
/// @return TRUE on success, else FALSE.
CALC_INLINE bool_t CALC_STDCALL bufcmp(const byte_t *const b1, const byte_t *const b2, size_t count)
{
	assert((b1 != NULL) && (b2 != NULL));

	CALC_REGISTER size_t i;
	CALC_REGISTER bool_t r = TRUE;

	for (i = 0; r && (i < count); i++)
		r = (b1[i] == b2[i]);

	return r;
}

/// @brief Checks if a portion of a given buffer content has
///        only zeros.
/// @param b The buffer to check.
/// @param count The number of bytes to check.
/// @return TRUE on success, else FALSE.
CALC_INLINE bool_t CALC_STDCALL bufnil(const byte_t *const b, size_t count)
{
	assert(b != NULL);

	CALC_REGISTER size_t i;
	CALC_REGISTER bool_t r = TRUE;

	for (i = 0; r && (i < count); i++)
		r = !((int)b[i]);

	return r;
}

/// @brief Counts the number of bytes before the terminator
///        character.
/// @param b The buffer to count.
/// @return The number of bytes before the terminator character.
CALC_INLINE size_t CALC_STDCALL buflen(const byte_t *const b)
{
	assert(b != NULL);

	CALC_REGISTER size_t i = 0;

	while (b[i])
		++i;

	return i;
}

// Buffer Conversion Function

#ifndef tobuf
/// @brief Converts a number to its buffer representation.
/// @param dest The buffer in wich copy bytes that compose the
///             number.
/// @param val The numeric value to convert.
/// @param count The number of bytes to write in the destination.
/// @return On success returns a pointer to the destination buffer.
#   define tobuf(dest, val, count) bufcpy((dest), (byte_t *)&(val), min((count), sizeof(val)))
#endif // tobuf

/// @brief Converts a number to its buffer representation. Unsigned
///        integer version.
/// @param dest The buffer in wich copy bytes that compose the
///             number.
/// @param val The numeric value to convert.
/// @param count The number of bytes to write in the destination.
/// @return On success returns a pointer to the destination buffer.
CALC_INLINE byte_t *CALC_STDCALL utobuf(byte_t *const dest, unsigned int val, size_t count)
{
	return tobuf(dest, val, count);
}

/// @brief Converts a number to its buffer representation. Unsigned
///        long integer version.
/// @param dest The buffer in wich copy bytes that compose the
///             number.
/// @param val The numeric value to convert.
/// @param count The number of bytes to write in the destination.
/// @return On success returns a pointer to the destination buffer.
CALC_INLINE byte_t *CALC_STDCALL ultobuf(byte_t *const dest, unsigned long val, size_t count)
{
	return tobuf(dest, val, count);
}

/// @brief Converts a number to its buffer representation. Unsigned
///        long long integer version.
/// @param dest The buffer in wich copy bytes that compose the
///             number.
/// @param val The numeric value to convert.
/// @param count The number of bytes to write in the destination.
/// @return On success returns a pointer to the destination buffer.
CALC_INLINE byte_t *CALC_STDCALL ulltobuf(byte_t *const dest, unsigned long long val, size_t count)
{
	return tobuf(dest, val, count);
}

/// @brief Converts a number to its buffer representation. Signed
///        integer version.
/// @param dest The buffer in wich copy bytes that compose the
///             number.
/// @param val The numeric value to convert.
/// @param count The number of bytes to write in the destination.
/// @return On success returns a pointer to the destination buffer.
CALC_INLINE byte_t *CALC_STDCALL itobuf(byte_t *const dest, int val, size_t count)
{
	return tobuf(dest, val, count);
}

/// @brief Converts a number to its buffer representation. Signed
///        long integer version.
/// @param dest The buffer in wich copy bytes that compose the
///             number.
/// @param val The numeric value to convert.
/// @param count The number of bytes to write in the destination.
/// @return On success returns a pointer to the destination buffer.
CALC_INLINE byte_t *CALC_STDCALL ltobuf(byte_t *const dest, long val, size_t count)
{
	return tobuf(dest, val, count);
}

/// @brief Converts a number to its buffer representation. Signed
///        long long integer version.
/// @param dest The buffer in wich copy bytes that compose the
///             number.
/// @param val The numeric value to convert.
/// @param count The number of bytes to write in the destination.
/// @return On success returns a pointer to the destination buffer.
CALC_INLINE byte_t *CALC_STDCALL lltobuf(byte_t *const dest, long long val, size_t count)
{
	return tobuf(dest, val, count);
}

/// @brief Converts a number to its buffer representation. Float
///        version.
/// @param dest The buffer in wich copy bytes that compose the
///             number.
/// @param val The numeric value to convert.
/// @param count The number of bytes to write in the destination.
/// @return On success returns a pointer to the destination buffer.
CALC_INLINE byte_t *CALC_STDCALL ftobuf(byte_t *const dest, float val, size_t count)
{
	return tobuf(dest, val, count);
}

/// @brief Converts a number to its buffer representation. Double
///        version.
/// @param dest The buffer in wich copy bytes that compose the
///             number.
/// @param val The numeric value to convert.
/// @param count The number of bytes to write in the destination.
/// @return On success returns a pointer to the destination buffer.
CALC_INLINE byte_t *CALC_STDCALL dtobuf(byte_t *const dest, double val, size_t count)
{
	return tobuf(dest, val, count);
}

/// @brief Converts a number to its buffer representation. Long
///        double version.
/// @param dest The buffer in wich copy bytes that compose the
///             number.
/// @param val The numeric value to convert.
/// @param count The number of bytes to write in the destination.
/// @return On success returns a pointer to the destination buffer.
CALC_INLINE byte_t *CALC_STDCALL ldtobuf(byte_t *const dest, long double val, size_t count)
{
	return tobuf(dest, val, count);
}

#ifndef bufto
/// @brief Converts a buffer into its numeric representation.
/// @param dest Destination variable in which copy the value.
/// @param source Source buffer form which copy the value.
/// @return A copy of the destination value.
#   define bufto(dest, source, count) bufcpy((byte_t *)&(dest), (source), min((count), sizeof(dest)));
#endif // bufto

/// @brief Converts a buffer into its numeric representation. Unsigned
///        int version.
/// @param buf The source buffer to convert.
/// @param count The number of bytes to convert.
/// @return The numeric value.
CALC_INLINE unsigned int CALC_CDECL buftou(const byte_t *const buf, size_t count)
{
	unsigned int tmp = 0;
	bufto(tmp, buf, count);
	return tmp;
}

/// @brief Converts a buffer into its numeric representation. Unsigned
///        long version.
/// @param buf The source buffer to convert.
/// @param count The number of bytes to convert.
/// @return The numeric value.
CALC_INLINE unsigned long CALC_CDECL buftoul(const byte_t *const buf, size_t count)
{
	unsigned long tmp = 0;
	bufto(tmp, buf, count);
	return tmp;
}

/// @brief Converts a buffer into its numeric representation. Unsigned
///        long long version.
/// @param buf The source buffer to convert.
/// @param count The number of bytes to convert.
/// @return The numeric value.
CALC_INLINE unsigned long long CALC_CDECL buftoull(const byte_t *const buf, size_t count)
{
	unsigned long long tmp = 0;
	bufto(tmp, buf, count);
	return tmp;
}

/// @brief Converts a buffer into its numeric representation.
///        Int version.
/// @param buf The source buffer to convert.
/// @param count The number of bytes to convert.
/// @return The numeric value.
CALC_INLINE int CALC_CDECL buftoi(const byte_t *const buf, size_t count)
{
	int tmp = 0;
	bufto(tmp, buf, count);
	return tmp;
}

/// @brief Converts a buffer into its numeric representation.
///        Long version.
/// @param buf The source buffer to convert.
/// @param count The number of bytes to convert.
/// @return The numeric value.
CALC_INLINE long CALC_CDECL buftol(const byte_t *const buf, size_t count)
{
	long tmp = 0;
	bufto(tmp, buf, count);
	return tmp;
}

/// @brief Converts a buffer into its numeric representation.
///        Long long version.
/// @param buf The source buffer to convert.
/// @param count The number of bytes to convert.
/// @return The numeric value.
CALC_INLINE long long CALC_CDECL buftoll(const byte_t *const buf, size_t count)
{
	long long tmp = 0;
	bufto(tmp, buf, count);
	return tmp;
}

/// @brief Converts a buffer into its numeric representation.
///        Float version.
/// @param buf The source buffer to convert.
/// @param count The number of bytes to convert.
/// @return The numeric value.
CALC_INLINE float CALC_CDECL buftof(const byte_t *const buf, size_t count)
{
	float tmp = 0;
	bufto(tmp, buf, count);
	return tmp;
}

/// @brief Converts a buffer into its numeric representation.
///        Double version.
/// @param buf The source buffer to convert.
/// @param count The number of bytes to convert.
/// @return The numeric value.
CALC_INLINE double CALC_CDECL buftod(const byte_t *const buf, size_t count)
{
	double tmp = 0;
	bufto(tmp, buf, count);
	return tmp;
}

/// @brief Converts a buffer into its numeric representation.
///        Long double version.
/// @param buf The source buffer to convert.
/// @param count The number of bytes to convert.
/// @return The numeric value.
CALC_INLINE long double CALC_CDECL buftold(const byte_t *const buf, size_t count)
{
	long double tmp = 0;
	bufto(tmp, buf, count);
	return tmp;
}

CALC_C_HEADER_END

#endif // CALC_BASE_BYTE_H_
