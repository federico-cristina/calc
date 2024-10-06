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
 * @brief       In this header are defined hashing types and functions to
 *              deal with them.
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

CALC_C_HEADER_END

#endif // CALC_CORE_HASH_H_
