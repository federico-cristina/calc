#pragma once

/**
 * @file        alloc.h
 * 
 * @author      Federico Cristina <federico.cristina@outlook.it>
 * 
 * @copyright   Copyright (c) 2024 Federico Cristina
 *              
 *              This file is part of the calc scripting language project,
 *              under the Apache License v2.0. See LICENSE for license
 *              informations.
 * 
 * @brief       In this header are defined macros, constants and functions
 *              to allocate and deallocate memory on the stack and on the
 *              heap ensuring memory safety.
 */

#ifndef CALC_BASE_ALLOC_H_
#define CALC_BASE_ALLOC_H_

#include "calc/base/error.h"

#if CALC_PLATFORM_IS_WINDOWS
#   include <malloc.h>
#endif

CALC_C_HEADER_BEGIN

/// @brief Checks if a memory block is a null pointer and in that case
///        aborts program execution showing an error message.
/// @param block Memory block to check.
/// @param errMsg Message that will be printed on the error stream in
///               case of failure (when the block is null).
/// @return The non-null block.
CALC_INLINE void *CALC_STDCALL _check(void *const block, const char *const errMsg)
{
    if (!block)
        return failno(errMsg);
    else
        return block;
}

#ifndef CALC_ALLOC_ERROR_MESSAGE
/// @brief This macro represent the default error message printed on the
///        error stream when the allocation of memory fails.
#   define CALC_ALLOC_ERROR_MESSAGE "cannot allocate memory"
#endif // CALC_ALLOC_ERROR_MESSAGE

#ifndef cmalloc
/// @brief Allocates a block of bytes of the same in the dynamic heap,
///        checking return value.
/// @param S The number of bytes to allocate.
/// @return A pointer to the new block of memory.
#   define cmalloc(S) _check(malloc((S)), CALC_ALLOC_ERROR_MESSAGE)
#endif // ccalloc

#ifndef alloc
/// @brief Allocates a block of bytes of the same dimension of the specified
///        data type.
/// @param T The type to allocate.
/// @return A pointer to the new block of memory.
#   define alloc(T) (T *)cmalloc(sizeof(T))
#endif // alloc

#ifndef ccalloc
/// @brief Allocates a series of N contiguous blocks of memory in the dynamic
///        heap, checking return value.
/// @param N The number of items to allocate.
/// @param S The size of each item to allocate.
/// @return A pointer to the new block of memory.
#   define ccalloc(N, S) _check(calloc((N), (S)), CALC_ALLOC_ERROR_MESSAGE)
#endif // ccalloc

#ifndef dim
/// @brief Allocates a series of N contiguous blocks of memory of the same
///        dimension of the specified data type.
/// @param T The type to allocate.
/// @param N The number of items to allocate.
/// @return A pointer to the new block of memory.
#   define dim(T, N) (T *)ccalloc(N, sizeof(T))
#endif // dim

/// @brief Frees a block of memory and returns a specified value.
/// @param toFree Block of memory to free.
/// @param retValue Value to return as result.
/// @return The value of retValue.
CALC_INLINE void *CALC_STDCALL freeret(void *toFree, void *retValue)
{
    return free(toFree), retValue;
}

#ifndef CALC_ALLOCA_ERROR_MESSAGE
/// @brief This macro represent the default error message printed on the
///        error stream when the allocation of memory on the stack fails.
#   define CALC_ALLOCA_ERROR_MESSAGE "cannot allocate memory on stack"
#endif // CALC_ALLOCA_ERROR_MESSAGE

#ifndef malloca
#   if CALC_PLATFORM_IS_WINDOWS
/// @brief Allocates a block of bytes on the stack checking that's not
///        NULL and failing in that case.
/// @param size The number of bytes to allocate.
/// @return A pointer to the new block of memory.
#       define malloca(size) _check(_malloca(size), CALC_ALLOCA_ERROR_MESSAGE)
#   else
/// @brief Allocates a block of bytes on the stack checking that's not
///        NULL and failing in that case.
/// @param size The number of bytes to allocate.
/// @return A pointer to the new block of memory.
#       define malloca(size) _check(alloca(size), CALC_ALLOCA_ERROR_MESSAGE)
#   endif
#endif // malloca

#ifndef freea
#   if CALC_PLATFORM_IS_WINDOWS
/// @brief Frees a block of memory allocated on the stack (or the heap) by
///        malloca.
/// @param block The previously allocated mempry block.
#       define freea(block) _freea(block)
#   else
/// @brief This function is Windows-specific, here it does nothing...
#       define freea(block)
#   endif
#endif // freea

#ifndef stackalloc
/// @brief Allocates a block of bytes of the same dimension of the specified
///        data type on the stack.
/// @param T The type to allocate.
/// @return A pointer to the new block of memory.
#   define stackalloc(T) (T *)malloca(sizeof(T))
#endif // stackalloc

#ifndef calloca
/// @brief Allocates a series of block of bytes on the stack, checking not
///        nullity of them and failing in that case.
/// @param count The number of blocks to allocate.
/// @param size The number of bytes to allocate.
/// @return A pointer to the new block of memory.
#   define calloca(count, size) malloca(count * size)
#endif // malloca

#ifndef stackdim
/// @brief Allocates a series of N contiguous blocks of memory of the same
///        dimension of the specified data type on the stack.
/// @param T The type to allocate.
/// @param N The number of items to allocate.
/// @return A pointer to the new block of memory.
#   define stackdim(T, N) (T *)calloca((N), sizeof(T))
#endif // stackdim

#ifndef alignto
/// @brief Gets an aligned number.
#   define alignto(size, alignment) ((size + alignment - 1) & ~(alignment - 1))
#endif // alignto

CALC_C_HEADER_END

#endif // CALC_BASE_ALLOC_H_
