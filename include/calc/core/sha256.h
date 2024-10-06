#pragma once

/**
 * @file        sha256.h
 *
 * @author      Federico Cristina <federico.cristina@outlook.it>
 *
 * @copyright   Copyright (c) 2024 Federico Cristina
 *
 *              This file is part of the calc scripting language project,
 *              under the Apache License v2.0. See LICENSE for license
 *              informations.
 *
 *              This file (like its .c implementation) is partially derived
 *              from files in the following repository:
 *
 *              https://github.com/B-Con/crypto-algorithms.git
 *
 * @brief       In this header are defined functions to encode and encrypt
 *              with SHA-256 algorithm.
 */

#ifndef CALC_CORE_SHA256_H_
#define CALC_CORE_SHA256_H_

#include "calc/base/api.h"
#include "calc/base/bits.h"
#include "calc/base/byte.h"

CALC_C_HEADER_BEGIN

#ifndef CALC_SHA256_KEY_SIZE
/// @brief SHA-256 input key size.
#   define CALC_SHA256_KEY_SIZE 64
#endif // CALC_SHA256_KEY_SIZE

#ifndef CALC_SHA256_BLOCK_SIZE
/// @brief SHA-256 output block size.
#   define CALC_SHA256_BLOCK_SIZE 32
#endif // CALC_SHA256_BLOCK_SIZE

/// @brief SHA-256 input key type.
typedef uint32_t CalcSha256HashKey_t[CALC_SHA256_KEY_SIZE];
/// @brief SHA-256 output block type.
typedef byte_t CalcSha256HashBlock_t[CALC_SHA256_BLOCK_SIZE];

/// @brief Holds the current state of the hash being computed.
typedef struct _CalcSha256Context
{
    /// @brief Input key.
    uint32_t key[64];
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
CALC_API CalcSha256Context_t *CALC_STDCALL calcSha256Update(CalcSha256Context_t *const ctx, const byte_t *const data, size_t count, const CalcSha256HashKey_t key);
/// @brief Computes the hash code block.
/// @param ctx A pointer to the SHA-256 context.
/// @param outHash The buffer in which write the output
///                hash bytes.
/// @return ctx parameter.
CALC_API CalcSha256Context_t *CALC_STDCALL calcSha256Final(CalcSha256Context_t *const ctx, byte_t *const outHash);

/// @brief Ecrypts a sequence of bytes
/// @param outHash The buffer in which write the output
///                hash bytes.
/// @param data A pointer to the buffer to use to fill
///             the context's data.
CALC_API void CALC_STDCALL calcSha256Encrypt(byte_t *const outHash, const byte_t *const data, const uint32_t *const key);

CALC_C_HEADER_END

#endif // CALC_CORE_BASE64_H_
