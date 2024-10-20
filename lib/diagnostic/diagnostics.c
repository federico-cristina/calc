/**
 * This file is part of the calc scripting language project,
 * under the Apache License v2.0. See LICENSE for license
 * informations.
 */

#include "calc/diagnostic/diagnostics.h"

// Diagnostic Code

CALC_API const char *CALC_STDCALL calcGetDiagnosticName(CalcDiagnosticCode_t diagnosticCode)
{
    switch (diagnosticCode)
    {
    case CALC_DIAGNOSTIC_CODE_E0000:
        return "E0000";

#pragma push_macro("calcDefineDiagnosticCode")

#ifndef calcDefineDiagnosticCode
        /// @brief Defines a diagnostic code using name parameter
        ///        prefixed with CALC_DIAGNOSTIC_CODE_.
#   define calcDefineDiagnosticCode(name, displayName, level, defaultFormat) \
    case CALC_DIAGNOSTIC_CODE_ ## name:                                      \
        return calcMacroToString(name);
#endif // calcDefineDiagnosticCode

#include CALC_DIAGNOSTIC_CODE_INC_

#ifdef calcDefineDiagnosticCode
#   undef calcDefineDiagnosticCode
#endif // UNDEF calcDefineDiagnosticCode

#pragma pop_macro("calcDefineDiagnosticCode")

    default:
        return unreach();
    }
}

CALC_API const char *CALC_STDCALL calcGetDiagnosticDisplayName(CalcDiagnosticCode_t diagnosticCode)
{
    switch (diagnosticCode)
    {
    case CALC_DIAGNOSTIC_CODE_E0000:
        return "NoError";

#pragma push_macro("calcDefineDiagnosticCode")

#ifndef calcDefineDiagnosticCode
        /// @brief Defines a diagnostic code using name parameter
        ///        prefixed with CALC_DIAGNOSTIC_CODE_.
#   define calcDefineDiagnosticCode(name, displayName, level, defaultFormat) \
    case CALC_DIAGNOSTIC_CODE_ ## name:                                      \
        return displayName;
#endif // calcDefineDiagnosticCode

#include CALC_DIAGNOSTIC_CODE_INC_

#ifdef calcDefineDiagnosticCode
#   undef calcDefineDiagnosticCode
#endif // UNDEF calcDefineDiagnosticCode

#pragma pop_macro("calcDefineDiagnosticCode")

    default:
        return unreach();
    }
}

CALC_API const char *CALC_STDCALL calcGetDiagnosticDefaultMessage(CalcDiagnosticCode_t diagnosticCode)
{
    switch (diagnosticCode)
    {
    case CALC_DIAGNOSTIC_CODE_E0000:
        return "no error has been reported.";

#pragma push_macro("calcDefineDiagnosticCode")

#ifndef calcDefineDiagnosticCode
        /// @brief Defines a diagnostic code using name parameter
        ///        prefixed with CALC_DIAGNOSTIC_CODE_.
#   define calcDefineDiagnosticCode(name, displayName, level, defaultFormat) \
    case CALC_DIAGNOSTIC_CODE_ ## name:                                      \
        return defaultFormat;
#endif // calcDefineDiagnosticCode

#include CALC_DIAGNOSTIC_CODE_INC_

#ifdef calcDefineDiagnosticCode
#   undef calcDefineDiagnosticCode
#endif // UNDEF calcDefineDiagnosticCode

#pragma pop_macro("calcDefineDiagnosticCode")

    default:
        return unreach();
    }
}

static CalcDiagnosticLevel_t calc_DiagnosticLevelsTable[] = {
#if CALC_C_STANDARD >= CALC_C_STANDARD_C99
    [CALC_DIAGNOSTIC_CODE_E0000] = CALC_DIAGNOSTIC_LEVEL_NONE,

#   pragma push_macro("calcDefineDiagnosticCode")

#   ifndef calcDefineDiagnosticCode
    /// @brief Defines a diagnostic code using name parameter
    ///        prefixed with CALC_DIAGNOSTIC_CODE_.
#      define calcDefineDiagnosticCode(name, displayName, level, defaultFormat) \
    [CALC_DIAGNOSTIC_CODE_ ## name] = CALC_DIAGNOSTIC_LEVEL_ ## level,
#   endif // calcDefineDiagnosticCode

#   include CALC_DIAGNOSTIC_CODE_INC_

#   ifdef calcDefineDiagnosticCode
#      undef calcDefineDiagnosticCode
#   endif // UNDEF calcDefineDiagnosticCode

#   pragma pop_macro("calcDefineDiagnosticCode")
#else
    CALC_DIAGNOSTIC_LEVEL_NONE,

#   pragma push_macro("calcDefineDiagnosticCode")

#   ifndef calcDefineDiagnosticCode
        /// @brief Defines a diagnostic code using name parameter
        ///        prefixed with CALC_DIAGNOSTIC_CODE_.
#       define calcDefineDiagnosticCode(name, displayName, level, defaultFormat) \
    CALC_DIAGNOSTIC_LEVEL_ ## level,
#   endif // calcDefineDiagnosticCode

#   include CALC_DIAGNOSTIC_CODE_INC_

#   ifdef calcDefineDiagnosticCode
#       undef calcDefineDiagnosticCode
#   endif // UNDEF calcDefineDiagnosticCode

#   pragma pop_macro("calcDefineDiagnosticCode")
#endif
};

CALC_API CalcDiagnosticLevel_t CALC_STDCALL calcGetDiagnosticLevel(CalcDiagnosticCode_t diagnosticCode)
{
    return calc_DiagnosticLevelsTable[diagnosticCode];
}

CALC_API void CALC_STDCALL calcSetDiagnosticLevel(CalcDiagnosticCode_t diagnosticCode, CalcDiagnosticLevel_t diagnosticLevel)
{
    calc_DiagnosticLevelsTable[diagnosticCode] = diagnosticLevel;

    return;
}

// Diagnostic Location

CALC_API CalcDiagnosticLocation_t *CALC_STDCALL calcInitDiagnosticLocation(CalcDiagnosticLocation_t *const location, char *const file, char *const func, char *const line, uint32_t lineNumber, uint16_t errorBegin, uint16_t errorLength, uint16_t errorPosition)
{
    location->file = file;
    location->func = func;
    location->line = line;
    location->lineNumber = lineNumber;
    location->errorBegin = errorBegin;
    location->errorLength = errorLength;
    location->errorPosition = errorPosition;

    return location;
}

CALC_API CalcDiagnosticLocation_t *CALC_STDCALL calcCreateDiagnosticLocation(char *const file, char *const func, char *const line, uint32_t lineNumber, uint16_t errorBegin, uint16_t errorLength, uint16_t errorPosition)
{
    return calcInitDiagnosticLocation(alloc(CalcDiagnosticLocation_t), file, func, line, lineNumber, errorBegin, errorLength, errorPosition);
}

// Diagnostic

CALC_API CalcDiagnostic_t *CALC_STDCALL calcCreateDiagnostic(CalcDiagnosticLevel_t level, int code, CalcDiagnosticLocation_t *const location, char *const message, bool_t cleanupMessage, char *const hint, bool_t cleanupHint)
{
    CalcDiagnostic_t *diagnostic = alloc(CalcDiagnostic_t);

    diagnostic->message = message;
    diagnostic->hint = hint;
    diagnostic->cleanupMessage = cleanupMessage;
    diagnostic->cleanupHint = cleanupHint;
    diagnostic->level = level;
    diagnostic->code = code;
    diagnostic->location = location;
    diagnostic->next = NULL;

    return diagnostic;
}

CALC_API void CALC_STDCALL calcDeleteDiagnostic(CalcDiagnostic_t *const diagnostic)
{
    if (diagnostic->cleanupMessage)
        free(diagnostic->message);

    if (diagnostic->cleanupHint)
        free(diagnostic->hint);

    free(diagnostic->location);
    free(diagnostic);

    return;
}
