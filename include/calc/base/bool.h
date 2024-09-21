#pragma once

/**
 * @file        bool.h
 * 
 * @author      Federico Cristina <federico.cristina@outlook.it>
 * 
 * @copyright   Copyright (c) 2024 Federico Cristina
 *              
 *              This file is part of the calc scripting language project,
 *              under the Apache License v2.0. See LICENSE for license
 *              informations.
 * 
 * @brief       In this header is defined onld-style boolean datatype
 *              with TRUE/FALSE constants.
 */

#ifndef CALC_BASE_BOOL_H_
#define CALC_BASE_BOOL_H_

#include "calc/base/defs.h"

CALC_C_HEADER_BEGIN

/// @brief Boolean data type. This is a type alias to emultate
///        the bool data type, its size is the same of an unsigned
///        char, but it should (logically) contain only TRUE (1)
///        or FALSE (0) constant values.
typedef unsigned char bool_t;

#ifndef FALSE
/// @brief This macro represents the boolean false value for the
///        bool_t data type.
#   define FALSE ((bool_t)0x00)
#elif FALSE
#   error FALSE must be false
#endif // FALSE

#ifndef TRUE
/// @brief This macro represents the boolean true value for the
///        bool_t data type.
#   define TRUE  ((bool_t)0x01)
#elif !TRUE
#   error TRUE must be true
#endif // TRUE

CALC_C_HEADER_END

#endif // CALC_BASE_BOOL_H_
