#pragma once

/**
 * @file        source_location.h
 *
 * @author      Federico Cristina <federico.cristina@outlook.it>
 *
 * @copyright   Copyright (c) 2024 Federico Cristina
 *
 *              This file is part of the calc scripting language project,
 *              under the Apache License v2.0. See LICENSE for license
 *              informations.
 *
 * @brief       In this header are defined structures and functions to
 *              manipulate source locations.
 */

#ifndef CALC_SOURCE_SOURCE_LOCATION_H_
#define CALC_SOURCE_SOURCE_LOCATION_H_

#include "calc/base/api.h"
#include "calc/base/bits.h"

#include <assert.h>

CALC_C_HEADER_BEGIN

/// @brief Source location data structure.
typedef struct _CalcSourceLocation
{
    /// @brief Current character number in the source stream.
    uint64_t ch;
    /// @brief Current column number in the source stream.
    uint32_t co;
    /// @brief Current line Number in the source stream.
    uint32_t ln;
} CalcSourceLocation_t;

/// @brief Sets the values of a source location.
/// @param sourceLocation The source location to set.
/// @param ch The number of the character in the source buffer.
/// @param co The number of the column in the source buffer.
/// @param ln The number of the line int the source buffer.
/// @return This function returns the sourceLocation parameter.
CALC_API_INLINE CalcSourceLocation_t *CALC_STDCALL calcSetSourceLocation(CalcSourceLocation_t *const sourceLocation, uint64_t ch, uint32_t co, uint32_t ln)
{
    assert(sourceLocation != NULL);

    sourceLocation->ch = ch;
    sourceLocation->co = co;
    sourceLocation->ln = ln;

    return sourceLocation;
}

CALC_C_HEADER_END

#endif // CALC_SOURCE_SOURCE_LOCATION_H_
