#pragma once

/**
 * 
 */

#ifndef CALC_BASE_DLOAD_H_
#define CALC_BASE_DLOAD_H_

#include "calc/base/bool.h"

CALC_C_HEADER_BEGIN

/// @brief Handle datatype.
typedef void *handle_t;

/// @brief Loads the handle for the current module.
/// @return An opaque handle to the current module.
CALC_EXTERN handle_t CALC_STDCALL dlload_current(void);
/// @brief Loads the specified dynamic (shared) library.
/// @param path The path to or the name of the dynamic
///             (shared) library to load.
/// @return An opaque handle to the specified module.
CALC_EXTERN handle_t CALC_STDCALL dlload(const char *const path);

/// @brief Imports a function from the module pointed
///        by the specified handle by its name.
/// @param handle The handle from which load the function.
/// @param name The name of the function to import.
/// @return An opaque handle to the imported function.
CALC_EXTERN handle_t CALC_STDCALL dlimpf(handle_t handle, const char *const name);

/// @brief Unloads the dynamic (shared) library pointed
///        by the handle from the memory.
/// @param handle The handle of the module to unload.
/// @return TRUE in case of success, else FALSE.
CALC_EXTERN bool_t CALC_STDCALL dlunload(handle_t handle);

CALC_C_HEADER_END

#endif // CALC_BASE_DLOAD_H_
