#pragma once

/**
 * @file        utils.h
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
 * @brief       In this header are defined utility macros to compare two
 *              numeric values, find the minimum or the maximum value between
 *              thwo numbers and check if an integer has a bitflag.
 */

#ifndef CALC_BASE_UTILS_H_
#define CALC_BASE_UTILS_H_

#ifndef numcmp
/**
 * @brief       Compares two numbers.
 * 
 * @param x     First number to compare.
 * @param y     Second number to compare.
 * @return      -1 if x is less than y, +1 if x is grater than y, or 0 if x and
 *              y have the same value.
 */
#   define numcmp(x, y) ((x) < (y) ? -1 : \
                         (x) > (y) ? +1 : 0)
#endif

#ifndef min
/**
 * @brief       Gets the minimum value between its two parameters.
 *
 * @param x     First number.
 * @param y     Second number.
 * @return      x if is less than y, else y.
 */
#   define min(x, y) (((x) < (y)) ? (x) : (y))
#endif

#ifndef max
/**
 * @brief       Gets the maximum value between its two parameters.
 *
 * @param x     First number.
 * @param y     Second number.
 * @return      x if is greater than y, else y.
 */
#   define max(x, y) (((x) > (y)) ? (x) : (y))
#endif

#ifndef hasflag
/**
 * @brief       Checks if an integral value has a bit flag.
 *
 * @param value Value to check.
 * @param flag  Bit flag to check.
 * @return      1 if value has the bit flag, else 0.
 */
#   define hasflag(value, flag) (((value) & (flag)) == (flag))
#endif

#endif /* CALC_BASE_UTILS_H_ */
