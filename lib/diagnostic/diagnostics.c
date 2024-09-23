#include "calc/diagnostic/diagnostics.h"

// Diagnostic Code

CALC_API const char *CALC_STDCALL calcGetDiagnosticDisplayName(CalcDiagnosticCode_t diagnosticCode)
{
    switch (diagnosticCode)
    {
    case CALC_DIAGNOSTIC_CODE_CE0000:
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
    case CALC_DIAGNOSTIC_CODE_CE0000:
        return "NoError";

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

CALC_API CalcDiagnosticLevel_t CALC_STDCALL calcGetDiagnosticLevel(CalcDiagnosticCode_t diagnosticCode)
{
    switch (diagnosticCode)
    {
    case CALC_DIAGNOSTIC_CODE_CE0000:
        return CALC_DIAGNOSTIC_LEVEL_ERROR;

#pragma push_macro("calcDefineDiagnosticCode")

#ifndef calcDefineDiagnosticCode
        /// @brief Defines a diagnostic code using name parameter
        ///        prefixed with CALC_DIAGNOSTIC_CODE_.
#   define calcDefineDiagnosticCode(name, displayName, level, defaultFormat) \
    case CALC_DIAGNOSTIC_CODE_ ## name:                                      \
        return CALC_DIAGNOSTIC_LEVEL_ ## level;
#endif // calcDefineDiagnosticCode

#include CALC_DIAGNOSTIC_CODE_INC_

#ifdef calcDefineDiagnosticCode
#   undef calcDefineDiagnosticCode
#endif // UNDEF calcDefineDiagnosticCode

#pragma pop_macro("calcDefineDiagnosticCode")

    default:
        return unreach(), 0;
    }
}

// Diagnostic Location

CALC_API CalcDiagnosticLocation_t *CALC_STDCALL calcInitDiagnosticLocation(CalcDiagnosticLocation_t *const location, char *const file, char *const func, char *const line, uint32_t lineNumber, uint16_t errorBegin, uint16_t errorLength, uint16_t errorPosition)
{
    location->file = file;
    location->func = func;
    location->line = line;
    location->lineNumber = lineNumber;
    location->errorBegin = errorBegin;
    location->errorLenght = errorLength;
    location->errorPosition = errorPosition;

    return location;
}

CALC_API CalcDiagnosticLocation_t *CALC_STDCALL calcCreateDiagnosticLocation(char *const file, char *const func, char *const line, uint32_t lineNumber, uint16_t errorBegin, uint16_t errorLength, uint16_t errorPosition)
{
    return calcInitDiagnosticLocation(alloc(CalcDiagnosticLocation_t), file, func, line, lineNumber, errorBegin, errorLength, errorPosition);
}

// Diagnostic

CALC_API CalcDiagnostic_t *CALC_STDCALL calcCreateDiagnostic(CalcDiagnosticLevel_t level, int code, CalcDiagnosticLocation_t *const location, char *const message)
{
    CalcDiagnostic_t *diagnostic = alloc(CalcDiagnostic_t);

    diagnostic->message = message;
    diagnostic->level = level;
    diagnostic->code = code;
    diagnostic->location = location;
    diagnostic->next = NULL;

    return diagnostic;
}

CALC_API void CALC_STDCALL calcDeleteDiagnostic(CalcDiagnostic_t *const diagnostic)
{
    free(diagnostic->message);
    free(diagnostic->location);
    free(diagnostic);

    return;
}
