#pragma once

/**
 * @file        hash.h
 *
 * @author      Federico Cristina <federico.cristina@outlook.it>
 *
 * @copyright   Copyright (c) 2024 Federico Cristina
 *
 *              This file is part of the calc scripting language project,
 *              under the Apache License v2.0. See LICENSE for license
 *              informations.
 *
 *              This file (and its .c implementation) is partially derived
 *              from files in the following repository:
 *
 *              https://github.com/B-Con/crypto-algorithms.git
 *
 * @brief       In this header are defined hashing types and functions to
 *              deal with them.
 *
 *              Supported hash functions:
 *
 *              - Simple
 *
 *              Sums the bytes of the key and returns that value. Is very
 *              fast and can be used easily with identifiers, but is not so
 *              great as hashing function.
 *
 *              - SHA-256
 *
 *              Hashes a sequence of bytes with a SHA-256 algorithm and sums
 *              the 32-bytes of the hash block produced by the SHA-256
 *              function.
 * 
 *              - Base64
 *
 *              Converts a sequence of bytes to its base64 representation
 *              and sums the produced output bytes.
 */

#ifndef CALC_CORE_HASH_H_
#define CALC_CORE_HASH_H_

#include "calc/base/api.h"
#include "calc/base/bits.h"
#include "calc/base/byte.h"

CALC_C_HEADER_BEGIN

/// @brief Hash code data type.
typedef uint32_t CalcHashCode_t;

/// @brief Hashing functions data type.
typedef CalcHashCode_t (*CalcHashFunc_t)(const byte_t *const);

/// @brief Simple hash code generator. Computes the hash code
///        of the specified key summing its characters.
/// @param key String to hash.
/// @return The just computed hash code.
CALC_API CalcHashCode_t CALC_STDCALL calcGetSimpleHashCode(const byte_t *const key);

// Base64 Conversion Functions

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

/// @brief Computes the key's hash code using base64 key's
///        representation.
/// @param key The key to hash.
/// @return The corresponding hash code.
CALC_API CalcHashCode_t CALC_STDCALL calcGetBase64HashCode(const byte_t *const key);

// SHA-256 Hashing Function

#ifndef CALC_SHA256_BLOCK_SIZE
/// @brief SHA-256 output block size.
#   define CALC_SHA256_BLOCK_SIZE 32
#endif // CALC_SHA256_BLOCK_SIZE

/// @brief SHA-256 output block type.
typedef byte_t *CalcSha256HashBlock_t;

/// @brief Holds the current state of the hash being computed.
typedef struct _CalcSha256Context
{
    /// @brief Messages bytes not hashed yet.
    byte_t   data[64];
    /// @brief The length of the data.
    uint32_t datalen;
    /// @brief 
    uint64_t bitlen;
    /// @brief The current chaining value.
    uint32_t state[8];
} CalcSha256Context_t;

/// @brief Initializes a SHA-256 context structure.
/// @param ctx The SHA-256 context to initialize.
/// @return This function returns ctx param.
CALC_API CalcSha256Context_t *CALC_STDCALL calcSha256ContextInit(CalcSha256Context_t *const ctx);
/// @brief Creates a SHA-256 context structure.
/// @return A pointer to the new SHA-256 context.
CALC_API CalcSha256Context_t *CALC_STDCALL calcCreateSha256Context(void);

/// @brief Updates the content of the SHA-256 context.
/// @param ctx A pointer to the SHA-256 to update.
/// @param data A pointer to the buffer to use to fill
///             the context's data.
/// @param count The number of bytes in data buffer.
/// @return ctx parameter.
CALC_API CalcSha256Context_t *CALC_STDCALL calcSha256Update(CalcSha256Context_t *const ctx, const byte_t *const data, size_t count);
/// @brief Computes the hash code block.
/// @param ctx A pointer to the SHA-256 context.
/// @param outHash The buffer in which write the output
///                hash bytes.
/// @return ctx parameter.
CALC_API CalcSha256Context_t *CALC_STDCALL calcSha256Final(CalcSha256Context_t *const ctx, byte_t *const outHash);

/// @brief Computes the key's hash code using SHA-256
///        hashing algorithm and packing it into a 32-bit
///        integer.
/// @param key The key to hash.
/// @return The corresponding hash code.
CALC_API CalcHashCode_t CALC_STDCALL calcGetSha256HashCode(const byte_t *const key);

CALC_C_HEADER_END

#endif // CALC_CORE_HASH_H_
