#pragma once

/**
 * @file        tokens.h
 *
 * @author      Federico Cristina <federico.cristina@outlook.it>
 *
 * @copyright   Copyright (c) 2024 Federico Cristina
 *
 *              This file is part of the calc scripting language project,
 *              under the Apache License v2.0. See LICENSE for license
 *              informations.
 *
 * @brief       In this header are defined tokens and functions to scan
 *              and manipulate them.
 */

#ifndef CALC_LEX_TOKENS_H_
#define CALC_LEX_TOKENS_H_

#include "calc/base/api.h"

CALC_C_HEADER_BEGIN

#ifndef CALC_LEX_TOKENS_INC_
/// @brief Location of the x-macro file containing infos about tokens.
#   define CALC_LEX_TOKENS_INC_ "calc/lex/tokens.inc"
#endif // CALC_LEX_TOKENS_INC_

/// @brief Enumerates token codes.
typedef enum _CalcTokenCode
{
    /// @brief Erroneous token code.
    CALC_TOKEN_INVALID = 0,

#pragma push_macro("calcDefineToken")

#ifndef calcDefineToken
    /// @brief Defines a token code using name parameter prefixed with
    ///        CALC_TOKEN_.
#   define calcDefineToken(name) name,
#endif // calcDefineToken

#include CALC_LEX_TOKENS_INC_

#ifdef calcDefineToken
#   undef calcDefineToken
#endif // UNDEF calcDefineToken

#pragma pop_macro("calcDefineToken")
} CalcTokenCode_t;

CALC_C_HEADER_END

#endif // CALC_LEX_TOKENS_H_
