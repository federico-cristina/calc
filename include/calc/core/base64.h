#pragma once

/**
 * 
 */

#ifndef CALC_CORE_BASE64_H_
#define CALC_CORE_BASE64_H_

#include "calc/base/api.h"
#include "calc/base/bits.h"
#include "calc/base/byte.h"

CALC_C_HEADER_BEGIN

/// @brief Encodes a sequence of bytes to base64 encoding.
/// @param key A pointer to the source sequence of bytes to
///            encode.
/// @param out A pointer to the destination buffer in which
///            write the encoded sequence of bytes. When set
///            to NULL the function returns the number of
///            bytes that should have been written in the out
///            buffer (the length of the output).
/// @param count The number of bytes in the source buffer.
/// @param newlineFlag When TRUE newlines are considered.
/// @return The length of the output byte sequence.
CALC_API size_t CALC_STDCALL calcBase64Encode(const byte_t *const key, byte_t *const out, size_t count, bool_t newlineFlag);
/// @brief Decodes a sequence of bytes from base64 encoding.
/// @param b64 A pointer to the encoded sequence of bytes to
///            decode.
/// @param out A pointer to the destination buffer in which
///            write the decoded sequence of bytes. When set
///            to NULL the function returns the number of
///            bytes that should have been written in the out
///            buffer (the length of the output).
/// @param count The number of bytes in the source buffer.
/// @return The length of the output byte sequence.
CALC_API size_t CALC_STDCALL calcBase64Decode(const byte_t *const b64, byte_t *const out, size_t count);

CALC_C_HEADER_END

#endif // CALC_CORE_BASE64_H_
