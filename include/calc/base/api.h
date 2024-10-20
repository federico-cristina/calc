#pragma once

/**
 * @file        api.h
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
 * @brief       In this header are defined utility macro for API constructions
 *              and use.
 */

#ifndef CALC_BASE_API_H_
#define CALC_BASE_API_H_

#include "calc/base/defs.h"

#ifndef CALC_API_PUBLIC
#   if !defined CALC_NO_DLL && !defined _NO_DLL
#       if CALC_BUILD_AS_DLL
/**
 * @brief       This constant marks a function as visible at the extern
 *              of the API in which is declared.
 */
#           define CALC_API_PUBLIC CALC_DLL_EXPORT
#       else
/**
 * @brief       This constant marks a function as visible at the extern
 *              of the API in which is declared.
 */
#           define CALC_API_PUBLIC CALC_DLL_IMPORT
#       endif
#   else
/**
 * @brief       This constant marks a function as visible at the extern
 *              of the API in which is declared.
 */
#       define CALC_API_PUBLIC
#   endif
#endif

#ifndef CALC_API_INLINE
#   if CALC_COMPILER_HAS_DECLSPEC
/**
 * @brief       This constant marks an inline function as visible at the
 *              extern of the API in which is declared, may be not supported.
 */
#       define CALC_API_INLINE CALC_API_PUBLIC CALC_INLINE
#   else
/**
 * @brief       This constant marks an inline function as visible at the
 *              extern of the API in which is declared, may be not supported.
 */
#       define CALC_API_INLINE CALC_INLINE
#   endif
#endif

#ifndef CALC_API_STATIC
/**
 * @brief       This constant marks a function as visible only in the
 *              scope of the API in which is declared.
 */
#   define CALC_API_STATIC CALC_DLL_STATIC
#endif

#ifndef CALC_API
/**
 * @brief       This constant marks a function as part of the current
 *              API.
 */
#   define CALC_API CALC_API_PUBLIC
#endif

#endif /* CALC_BASE_API_H_ */
