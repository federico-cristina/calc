#pragma once

/**
 * @file        error.h
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
 * @brief       In this header are defined macros and functions to handle
 *              internal fatal and non-fatal errors and.
 */

#ifndef CALC_BASE_ERROR_H_
#define CALC_BASE_ERROR_H_

#include "calc/base/errno.h"

#include <stdlib.h>
#include <setjmp.h>

CALC_C_HEADER_BEGIN

/**
 * @defgroup    FATAL_ERRORS_HANDLING Fatal Errors Handling
 * @{
 */

#pragma region Fatal Errors Handling

#ifndef CALC_ERROR_TRACE_SPACES
/**
 * @brief       This constant represents the default number of spaces used at the
 *              beginning of an error trace. (It can be used to build error messages)
 */
#   define CALC_ERROR_TRACE_SPACES "    "
#endif

#ifndef CALC_ERROR_TRACE_STRING
#   if CALC_C_STANDARD >= CALC_C_STANDARD_C99
/**
 * @brief       This constant represents the default internal error trace string used
 *              (in fail macros) to show in which file and in which function has been
 *              thrown the error.
 */
#       define CALC_ERROR_TRACE_STRING "\n" CALC_ERROR_TRACE_SPACES "at %s in %s:%lld"
#   else
/**
 * @brief       This constant represents the default internal error trace string used
 *              (in fail macros) to show in which file and in which function has been
 *              thrown the error.
 */
#       define CALC_ERROR_TRACE_STRING "\n" CALC_ERROR_TRACE_SPACES "in %s:%ld"
#   endif
#endif

#if CALC_DEBUG

#if CALC_C_STANDARD >= CALC_C_STANDARD_C99
/**
 * @brief       This function shows an error message supposing that that error is not
 *              fatal.
 * 
 * @param       format Format string of the message to print.
 * @param       others Arguments to use to format the message.
 */
CALC_INLINE void CALC_CDECL _warn(const char *const format, const char *const func, const char *const file, long long line, ...)
#else
/**
 * @brief       This function shows an error message supposing that that error is not
 *              fatal.
 * 
 * @param       format Format string of the message to print.
 * @param       others Arguments to use to format the message.
 */
CALC_INLINE void CALC_CDECL _warn(const char *const format, const char *const file, long long line, ...)
#endif
{
    va_list arglist;

    va_start(arglist, line);
    veprintf(format, arglist);
    va_end(arglist);

#if CALC_C_STANDARD >= CALC_C_STANDARD_C99
    eprintfn(CALC_ERROR_TRACE_STRING, func, file, line);
#else
    eprintfn(CALC_ERROR_TRACE_STRING, file, line);
#endif

    return;
}

#if CALC_C_STANDARD >= CALC_C_STANDARD_C99
/**
 * @brief       This function aborts program execution printing a formatted error
 *              message on the error stream.
 * 
 * @param       format Format string of the message to print.
 * @param       others Arguments to use to format the message.
 */
CALC_INLINE CALC_NORETURN void CALC_CDECL _fail(const char *const format, const char *const func, const char *const file, long long line, ...)
#else
/**
 * @brief       This function aborts program execution printing a formatted error
 *              message on the error stream.
 * 
 * @param       format Format string of the message to print.
 * @param       others Arguments to use to format the message.
 */
CALC_INLINE CALC_NORETURN void CALC_CDECL _fail(const char *const format, const char *const file, long long line, ...)
#endif
{
    va_list arglist;

    va_start(arglist, line);
    veprintf(format, arglist);
    va_end(arglist);

#if CALC_C_STANDARD >= CALC_C_STANDARD_C99
    eprintfn(CALC_ERROR_TRACE_STRING, func, file, line);
#else
    eprintfn(CALC_ERROR_TRACE_STRING, file, line);
#endif

    abort();
}

#else

/**
 * @brief       This function shows an error message supposing that that error is not
 *              fatal.
 * 
 * @param       format Format string of the message to print.
 * @param       others Arguments to use to format the message.
 */
CALC_INLINE void CALC_CDECL _warn(const char *const format, ...)
{
    va_list arglist;

    va_start(arglist, format);
    veprintf(format, arglist);
    va_end(arglist);

    return;
}

/**
 * @brief       This function aborts program execution printing a formatted error
 *              message on the error stream.
 * 
 * @param       format Format string of the message to print.
 * @param       others Arguments to use to format the message.
 */
CALC_INLINE CALC_NORETURN void CALC_CDECL _fail(const char *const format, ...)
{
    va_list arglist;

    va_start(arglist, format);
    veprintfn(format, arglist);
    va_end(arglist);

    abort();
}

#endif

#ifndef warn
#   if CALC_DEBUG
#       if CALC_C_STANDARD >= CALC_C_STANDARD_C99
/**
 * @brief       While debugging reports a non fatal error with the position into
 *              the source code.
 * 
 * @param       format A constant string defining the format of the error message
 *              to print.
 * @param       others The arguments to use to format.
 */
#           define warn(format, ...) _warn(format, __func__, __FILE__, __LINE__, __VA_ARGS__)
#       else
/**
 * @brief       While debugging reports a non fatal error with the position into
 *              the source code.
 * 
 * @param       format A constant string defining the format of the error message
 *              to print.
 * @param       others The arguments to use to format.
 */
#           define warn(format, ...) _warn(format, __FILE__, __LINE__, __VA_ARGS__)
#       endif
#   else
/**
 * @brief       While debugging reports a non fatal error with the position into
 *              the source code.
 * 
 * @param       format A constant string defining the format of the error message
 *              to print.
 * @param       others The arguments to use to format.
 */
#       define warn(format, ...) _warn(format, __VA_ARGS__)
#   endif
#endif

#ifndef fail
#   if CALC_DEBUG
#       if CALC_C_STANDARD >= CALC_C_STANDARD_C99
/**
 * @brief       While debugging aborts printing the name of function from where
 *              has been reported the fatal error.
 * 
 * @param       format A constant string defining the format of the error message
 *              to print.
 * @param       others The arguments to use to format.
 */
#           define fail(format, ...) _fail(format, __func__, __FILE__, __LINE__, __VA_ARGS__)
#       else
/**
 * @brief       While debugging aborts printing the name of function from where
 *              has been reported the fatal error.
 * 
 * @param       format A constant string defining the format of the error message
 *              to print.
 * @param       others The arguments to use to format.
 */
#           define fail(format, ...) _fail(format, __FILE__, __LINE__, __VA_ARGS__)
#       endif
#   else
/**
 * @brief       While debugging aborts printing the name of function from where
 *              has been reported the fatal error.
 * 
 * @param       format A constant string defining the format of the error message
 *              to print.
 * @param       others The arguments to use to format.
 */
#       define fail(format, ...) _fail(format, __VA_ARGS__)
#   endif
#endif

#ifndef notice
/**
 * @brief       Reports an error.
 * 
 * @param       essage An additional message to print to explain the error.
 */
#   define notice(message) (warn("error: %s", (message)), NULL)
#endif

#ifndef failno
/**
 * @brief       Aborts program execution printing an error message based on
 *              the current value of errno.
 * 
 * @param       essage An additional message to print to explain the error.
 */
#   define failno(message) (fail("errno %d (%s): %s (%s)", errno, errnoname(errno), (message), strerror(errno)), NULL)
#endif

#ifndef unreach
/**
 * @brief       This macro marks a portion of code which normally cannot be
 *              reached without some errors. So, when unreachable code is
 *              reached, there must be an error (maybe uknown) and so fails.
 */
#   define unreach() (fail("error: unreachable code has been reached", NULL), NULL)
#endif

#ifndef noimpl
/**
 * @brief       This macro marks a portion of code not yet implemented and so
 *              fails when reach it.
 */
#   define notimpl() (fail("error: not implemented yet", NULL), NULL)
#endif

#pragma endregion

/**
 * @}
 * 
 * @defgroup    NON_FATAL_ERRORS_HANDLING Non-fatal Errors Handling
 * @{
 */

#pragma region Non-fatal Errors Handling

/**
 * @brief       Pushes on the top of the jmpstack the value of buf.
 * 
 * @param       buf Saved status to push onto the jmpstack.
 */
CALC_EXTERN void CALC_STDCALL jmptop(jmp_buf *const buf);
/**
 * @brief       Pops the top of the jmpstack, deleting it.
 */
CALC_EXTERN void CALC_STDCALL jmppop(void);

/**
 * @brief       Callback datatype.
 */
typedef int (*callback_t)(int);

/**
 * @brief       Helper function for jmpback macro.
 * 
 * @warning     DON'T CALL THIS FUNCTION DIRECTLY.
 */
CALC_INLINE int CALC_STDCALL _jmpback(int value, jmp_buf *const buf, callback_t callback)
{
    CALC_REGISTER int result;

    if (value)
        result = callback(value);
    else
        result = 0, jmptop(buf);

    return result;
}

#ifndef jmpback
/**
 * @brief       Saves the current status of the program into buf, when longjmp
 *              function the control returns to this function that calls a
 *              callback function to handle the longjmp signal value.
 * 
 * @param       buf The jmp_buf in which save the current execution status.
 * @param       callback Callback function address.
 * @return      Zero when the error status has been saved correcly, else the
 *              value passed to longjmp function when has been called.
 */
#   define jmpback(buf, callback) _jmpback(setjmp(buf), &(buf), (callback))
#endif

/**
 * @brief       Jumps to the last jmp_buf on the jmpstack, or fails the execution
 *              if there's no one.
 * 
 * @param       value Value of the signal to report to the handler.
 */
CALC_EXTERN CALC_NORETURN void CALC_STDCALL jump(int value);

#pragma endregion

/**
 * @}
 */

CALC_C_HEADER_END

#endif /* CALC_BASE_ERROR_H_ */
