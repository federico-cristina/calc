#pragma once

/**
 * @file        result.h
 *
 * @author      Federico Cristina <federico.cristina@outlook.it>
 *
 * @copyright   Copyright (c) 2024 Federico Cristina
 *
 *              This file is part of the calc scripting language project,
 *              under the Apache License v2.0. See LICENSE for license
 *              informations.
 *
 * @brief       In this header is defined the CalcResult_t datatype, used
 *              to notice success of failure of a function.
 */

#ifndef CALC_CORE_RESULT_H_
#define CALC_CORE_RESULT_H_

#include "calc/base/defs.h"

CALC_C_HEADER_BEGIN

 /// @brief Enumerates possible states (SUCCESS or FAILURE) of the
 ///        result of an operation.
typedef enum _CalcResult
{
    /// @brief Success status.
    CALC_SUCCESS = 1,
    /// @brief Failure status.
    CALC_FAILURE = 0,
} CalcResult_t;

CALC_C_HEADER_END

#endif // CALC_CORE_RESULT_H_
