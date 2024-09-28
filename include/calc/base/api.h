#pragma once

/**
 * @file        api.h
 *
 * @author      Federico Cristina <federico.cristina@outlook.it>
 *
 * @copyright   Copyright (c) 2024 Federico Cristina
 *
 *              This file is part of the calc scripting language project,
 *              under the Apache License v2.0. See LICENSE for license
 *              informations.
 *
 * @brief       In this header are defined utility macro to functions
 *              exportations while building shared libraries.
 */

#ifndef CALC_BASE_API_H_
#define CALC_BASE_API_H_

#include "calc/base/defs.h"

#ifdef CALC_NO_DLL
#   ifndef CALC_API_PUB
/// @brief This macro marks a function to be exported
///        while building a dynamic library.
#       define CALC_API_PUB
#   endif // CALC_API_PUB
#endif

#ifndef CALC_API_PUB
#   if CALC_BUILD_AS_DLL
/// @brief This macro marks a function to be exported
///        while building a dynamic library.
#       define CALC_API_PUB CALC_DLL_EXPORT
#   else
/// @brief This macro marks a function to be imported
///        while building a dynamic library.
#       define CALC_API_PUB CALC_DLL_IMPORT
#   endif // CALC_API_PUB
#endif // CALC_API

#ifndef CALC_API_LOC
/// @brief This macro marks a function to be hidden
///        while building a dynamic library.
#   define CALC_API_LOC CALC_DLL_STATIC
#endif // CALC_API_LOC

#ifndef CALC_API
/// @brief This macro marks a function as an API
///        function. By default API functions are
///        public.
#   define CALC_API CALC_API_PUB
#endif // CALC_API

#ifndef CALC_API_INLINE
/// @brief This macro marks a function as an API
///        function that can be inlined.
#   define CALC_API_INLINE CALC_API_PUB CALC_INLINE
#endif // CALC_API_INLINE

#endif // CALC_BASE_API_H_
