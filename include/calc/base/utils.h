#pragma once

/**
 * @file        utils.h
 *
 * @author      Federico Cristina <federico.cristina@outlook.it>
 *
 * @copyright   Copyright (c) 2024 Federico Cristina
 *
 *              This file is part of the calc scripting language project,
 *              under the Apache License v2.0. See LICENSE for license
 *              informations.
 *
 * @brief       In this header are defined utility macros to compare two
 *              numeric values, find the minimum value and find the maximum
 *              value.
 */

#ifndef CALC_BASE_UTILS_H_
#define CALC_BASE_UTILS_H_

#ifndef numcmp
/// @brief Compares two numbers.
/// @param x First number to compare.
/// @param y Second number to compare.
/// @return -1 if x is less than y, +1 if x is grater than y, or
///         0 if x and y have the same value.
#   define numcmp(x, y) ((x) < (y) ? -1 : \
                         (x) > (y) ? +1 : 0)
#endif // numcmp

#ifndef min
/// @brief Gets the minimum value between its two parameters.
/// @param size1 First size.
/// @param size2 Second size.
/// @return size1 if is less than size2, else size2.
#   define min(size1, size2) (((size1) < (size2)) ? (size1) : (size2))
#endif // min

#ifndef max
/// @brief Gets the maximum value between its two parameters.
/// @param size1 First size.
/// @param size2 Second size.
/// @return size1 if is greater than size2, else size2.
#   define max(size1, size2) (((size1) > (size2)) ? (size1) : (size2))
#endif // max

#ifndef hasflag
/// @brief Checks if an integral value has a bit flag.
/// @param value Value to check.
/// @param flag Bit flag to check.
/// @return 1 if value has the bit flag, else 0.
#   define hasflag(value, flag) (((value) & (flag)) == (flag))
#endif // hasflag

#endif // CALC_BASE_UTILS_H_
