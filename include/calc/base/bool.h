#pragma once

/**
 * @file        bool.h
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
 * @brief       In this header is defined old-style boolean datatype with
 *              TRUE/FALSE constants.
 */

#ifndef CALC_BASE_BOOL_H_
#define CALC_BASE_BOOL_H_

#include "calc/base/defs.h"

CALC_C_HEADER_BEGIN

/**
 * @brief       Boolean datatype. This is a type alias to emultate the bool
 *              datatype, its size is the same of an unsigned char, but it
 *              should (logically) contain only `TRUE` (1) or `FALSE` (0)
 *              constant values.
 */
typedef unsigned char bool_t;

#ifndef FALSE
/**
 * @brief       This constant represents the boolean false value for the `bool_t`
 *              datatype.
 */
#   define FALSE ((bool_t)0x00)
#elif   FALSE
#   error FALSE must be false
#endif

#ifndef TRUE
/**
 * @brief       This constant represents the boolean true value for the `bool_t`
 *              datatype.
 */
#   define TRUE  ((bool_t)0x01)
#elif  !TRUE
#   error TRUE must be true
#endif

CALC_C_HEADER_END

#endif /* CALC_BASE_BOOL_H_ */
