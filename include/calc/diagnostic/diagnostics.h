#pragma once

/**
 * @file        diagnostics.h
 *
 * @author      Federico Cristina <federico.cristina@outlook.it>
 *
 * @copyright   Copyright (c) 2024 Federico Cristina
 *
 *              This file is part of the calc scripting language project,
 *              under the Apache License v2.0. See LICENSE for license
 *              informations.
 *
 * @brief       In this header are defined diagnostics kinds, codes and
 *              data structures to store them informations.
 */

#ifndef CALC_DIAGNOSTIC_DIAGNOSTICS_H_
#define CALC_DIAGNOSTIC_DIAGNOSTICS_H_

#include "calc/base/api.h"
#include "calc/base/bits.h"
#include "calc/base/string.h"

CALC_C_HEADER_BEGIN

// Diagnostic Level

/// @brief Diagnostic levels enumeration.
typedef enum _CalcDiagnosticLevel
{
    /// @brief A suppressed diagnostic represents something
    ///        that was an error or a warning, but the user
    ///        suppressed it.
    CALC_DIAGNOSTIC_LEVEL_SUPPRESSED = -2,
    /// @brief An errno diagnostic represents an internal C
    ///        diagnostic base on errno value.
    CALC_DIAGNOSTIC_LEVEL_ERRNO,
    /// @brief A diagnostic without any error level, it won't
    ///        be emitted.
    CALC_DIAGNOSTIC_LEVEL_NONE,
    /// @brief A note diagnostic represents something that's
    ///        not an error, but is better to notice.
    CALC_DIAGNOSTIC_LEVEL_NOTE,
    /// @brief A warning diagnostic indicate something that
    ///        is not a problem but can be, like for unsafe
    ///        operations.
    CALC_DIAGNOSTIC_LEVEL_WARNING,
    /// @brief An error diagnostic indicate a problem in the
    ///        source code. Like a syntactic error. Once is
    ///        thrown the analysis continue but the analysed
    ///        source will not be compilated/executed.
    CALC_DIAGNOSTIC_LEVEL_ERROR,
    /// @brief A fatal error diagnostic indicate a problem
    ///        that can compromise next analysis stages.
    CALC_DIAGNOSTIC_LEVEL_FATAL,
} CalcDiagnosticLevel_t;

/// @brief Maps each diagnostic level code to a custom string
///        representig the error message prefix.
/// @param level Diagnostic error level code.
/// @return A constant pointer to a constant string containing
///         the error message prefix.
CALC_API_INLINE const char *CALC_STDCALL calcGetDiagnosticLevelName(CalcDiagnosticLevel_t level)
{
    switch (level)
    {
    case CALC_DIAGNOSTIC_LEVEL_SUPPRESSED:
        return "suppressed";

    case CALC_DIAGNOSTIC_LEVEL_ERRNO:
        return "errno";

    case CALC_DIAGNOSTIC_LEVEL_NONE:
        return "none";

    case CALC_DIAGNOSTIC_LEVEL_NOTE:
        return "note";

    case CALC_DIAGNOSTIC_LEVEL_WARNING:
        return "warning";

    case CALC_DIAGNOSTIC_LEVEL_ERROR:
        return "error";

    case CALC_DIAGNOSTIC_LEVEL_FATAL:
        return "fatal error";

    default:
        return unreach();
    }
}

// Diagnostic Code

#ifndef CALC_DIAGNOSTIC_CODE_INC_
/// @brief Location of the x-macro file containing infos
///        about diagnostics.
#   define CALC_DIAGNOSTIC_CODE_INC_ "calc/diagnostic/diagnostics.inc"
#endif // CALC_DIAGNOSTIC_CODE_INC_

/// @brief Enumerates each specific diagnostic code.
typedef enum _CalcDiagnosticCode
{
    /// @brief NoError: No error has been reported.
    CALC_DIAGNOSTIC_CODE_E0000 = 0,

#pragma push_macro("calcDefineDiagnosticCode")

#ifndef calcDefineDiagnosticCode
    /// @brief Defines a diagnostic code using name parameter
    ///        prefixed with CALC_DIAGNOSTIC_CODE_.
#   define calcDefineDiagnosticCode(name, displayName, level, defaultFormat) CALC_DIAGNOSTIC_CODE_ ## name,
#endif // calcDefineDiagnosticCode

#include CALC_DIAGNOSTIC_CODE_INC_

#ifdef calcDefineDiagnosticCode
#   undef calcDefineDiagnosticCode
#endif // UNDEF calcDefineDiagnosticCode

#pragma pop_macro("calcDefineDiagnosticCode")
} CalcDiagnosticCode_t;

/// @brief Maps each diagnostic code to its relative name.
/// @param code Diagnostic code to map.
/// @return A constant pointer to the constant string containing
///         the name of the diagnostic.
CALC_API const char *CALC_STDCALL calcGetDiagnosticName(CalcDiagnosticCode_t diagnosticCode);
/// @brief Maps each diagnostic code to its relative display
///        name.
/// @param code Diagnostic code to map.
/// @return A constant pointer to the constant string containing
///         the display name of the diagnostic.
CALC_API const char *CALC_STDCALL calcGetDiagnosticDisplayName(CalcDiagnosticCode_t diagnosticCode);
/// @brief Maps each diagnostic code to its relative default
///        format string.
/// @param code Diagnostic code to map.
/// @return A constant pointer to the constant string containing
///         the name of the diagnostic.
CALC_API const char *CALC_STDCALL calcGetDiagnosticDefaultMessage(CalcDiagnosticCode_t diagnosticCode);
/// @brief Maps each diagnostic code to its relative level
///        code.
/// @param code Diagnostic code to map.
/// @return A constant pointer to the constant string containing
///         the name of the diagnostic.
CALC_API CalcDiagnosticLevel_t CALC_STDCALL calcGetDiagnosticLevel(CalcDiagnosticCode_t diagnosticCode);

/// @brief Sets the level of an diagnostic code.
/// @param diagnosticCode Diagnostic code to set.
/// @param diagnosticLevel New error level.
CALC_API void CALC_STDCALL calcSetDiagnosticLevel(CalcDiagnosticCode_t diagnosticCode, CalcDiagnosticLevel_t diagnosticLevel);

// Diagnostic Location

/// @brief Diagnostic location data structure.
typedef struct _CalcDiagnosticLocation
{
    /// @brief Name (or path) to the file from which the current
    ///        diagnostic refers to.
    char    *file;
    /// @brief Name of the source function.
    char    *func;
    /// @brief A reference of the line from which is originated the
    ///        problem.
    char    *line;
    /// @brief The number of the line from which is originated the
    ///        problem.
    uint32_t lineNumber;
    /// @brief The number of the character where the line where begins
    ///        the erroneous sequence.
    uint16_t errorBegin;
    /// @brief The length of the erroneous sequence.
    uint16_t errorLength;
    /// @brief The exact position of the error in the line.
    uint16_t errorPosition;
} CalcDiagnosticLocation_t;

/// @brief Initializes a CalcDiagnosticLocation data structure with
///        error location informations.
/// @param location A pointer to the structure to initialize.
/// @param file The name of the file form which has been originated
///             the problem.
/// @param func The name of the function form which has been originated
///             the problem.
/// @param line A pointer to the beginning of the line from which has
///             been originated the error.
/// @param lineNumber The number of the line.
/// @param errorBegin The number of the character where begins the erroneous
///                   sequence.
/// @param errorLength The length of the erroneous sequence.
/// @param errorPosition The exact position of the error in the line.
/// @return On success location is returned.
CALC_API CalcDiagnosticLocation_t *CALC_STDCALL calcInitDiagnosticLocation(CalcDiagnosticLocation_t *const location, char *const file, char *const func, char *const line, uint32_t lineNumber, uint16_t errorBegin, uint16_t errorLength, uint16_t errorPosition);
/// @brief Creates a new CalcDiagnosticLocation data structure with
///        error location informations.
/// @param file The name of the file form which has been originated
///             the problem.
/// @param func The name of the function form which has been originated
///             the problem.
/// @param line A pointer to the beginning of the line from which has
///             been originated the error.
/// @param lineNumber The number of the line.
/// @param errorBegin The number of the character where begins the erroneous
///                   sequence.
/// @param errorLength The length of the erroneous sequence.
/// @param errorPosition The exact position of the error in the line.
/// @return A pointer to the new CalcDiagnosticLocation data structure.
CALC_API CalcDiagnosticLocation_t *CALC_STDCALL calcCreateDiagnosticLocation(char *const file, char *const func, char *const line, uint32_t lineNumber, uint16_t errorBegin, uint16_t errorLength, uint16_t errorPosition);

#ifndef calcGetCurrentLocation
/// @brief Creates a new diagnostic location based on the current
///        location in the C/C++ source file.
/// @return A pointer to the new allocated diagnostic location.
#   define calcGetCurrentLocation() calcCreateDiagnosticLocation(__FILE__, __func__, NULL, __LINE__, 0, 0, 0)
#endif // calcGetCurrentLocation

// Diagnostic

/// @brief Diagnostic data structure.
typedef struct _CalcDiagnostic
{
    /// @brief Diangostic message to display with diagnostic code.
    char                     *message;
    /// @brief Diangostic hint to display with diagnostic trace.
    char                     *hint;
    /// @brief This flag specifies that on deletion of the diagnostic
    ///        the message must be deleted too.
    bool_t                    cleanupMessage;
    /// @brief This flag specifies that on deletion of the diagnostic
    ///        the hint must be deleted too.
    bool_t                    cleanupHint;
    /// @brief Diagnostic level to choose what do after displayed
    ///        the message.
    CalcDiagnosticLevel_t     level;
    /// @brief Diagnostic code to display with diagnostic message,
    ///        can refer to an errno or to a diagnostic code.
    int                       code;
    /// @brief Location from which the problem has been originated.
    CalcDiagnosticLocation_t *location;
    /// @brief Next diagnostic in the stack.
    struct _CalcDiagnostic   *next;
} CalcDiagnostic_t;

/// @brief Creates a new diagnostic data structure to store informations
///        about a problematic occurred during the process without force
///        execution termination.
/// @param level Diagnostic level to choose what do after displayed
///              the message.
/// @param code Diagnostic code to display with diagnostic message.
/// @param location Location from which the problem has been originated.
/// @param message Diangostic message to display with diagnostic code.
/// @param cleanupMessage Specifies that on deletion of the diagnostic
///                       the message must be deleted too.
/// @param hint Diangostic hint to display with diagnostic trace.
/// @param cleanupMessage Specifies that on deletion of the diagnostic
///                       the hint must be deleted too.
/// @return A pointer to new allocated diagnostic informations record.
CALC_API CalcDiagnostic_t *CALC_STDCALL calcCreateDiagnostic(CalcDiagnosticLevel_t level, int code, CalcDiagnosticLocation_t *const location, char *const message, bool_t cleanupMessage, char *const hint, bool_t cleanupHint);

/// @brief Suppress a diagnostic.
/// @param code Diagnostic code to suppress.
CALC_API_INLINE void CALC_STDCALL calcSuppressDiagnostic(CalcDiagnosticCode_t code)
{
    calcSetDiagnosticLevel(code, CALC_DIAGNOSTIC_LEVEL_SUPPRESSED);

    return;
}

#ifndef calcCreateDiagnosticFromCode
/// @brief Creates a new diagnostic from a specific diagnostic code.
#   define calcCreateDiagnosticFromCode(code, location, ...) calcCreateDiagnostic(calcGetDiagnosticLevel(code), (int)(code), (location), strfmt(calcGetDiagnosticDefaultMessage(code), __VA_ARGS__), TRUE, NULL, FALSE)
#endif // calcCreateDiagnosticFromCode

#ifndef calcCreateDiagnosticFromErrno
/// @brief Creates a new diagnostic from the value of errno.
#   define calcCreateDiagnosticFromErrno(format, ...) calcCreateDiagnostic(CALC_DIAGNOSTIC_LEVEL_ERRNO, errno, calcGetCurrentLocation(), strfmt((format), __VA_ARGS__), TRUE, NULL, FALSE)
#endif // calcCreateDiagnosticFromErrno

/// @brief Deletes a diagnostic data structure.
/// @param diagnostic Diagnostic data structure to delete.
CALC_API void CALC_STDCALL calcDeleteDiagnostic(CalcDiagnostic_t *const diagnostic);

CALC_C_HEADER_END

#endif // CALC_DIAGNOSTIC_DIAGNOSTICS_H_
