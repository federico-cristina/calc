#include "calc/diagnostic/emitter.h"

CALC_API int CALC_STDCALL calcEmitDiagnosticLocation(CalcDiagnosticLocation_t *const diagnosticLocation, FILE *const stream, bool_t useColors)
{
    int result;

    if (useColors)
        fputs("\x1B[0;97m", stream); // color: BRIGHT WHITE

    result = fprintf(stream, "%s:%u:", diagnosticLocation->file, diagnosticLocation->lineNumber);

    if (diagnosticLocation->errorPosition)
        result += fprintf(stream, "%u:", diagnosticLocation->errorPosition);

    if (useColors)
        fputs("\x1B[0m", stream); // color: RESET

    return result;
}

CALC_API int CALC_STDCALL calcEmitDiagnosticTrace(char *const hint, CalcDiagnosticLocation_t *const diagnosticLocation, FILE *const stream, bool_t useColors)
{
    int result = 0;

    if (diagnosticLocation->line)
    {
        char *line = diagnosticLocation->line;

        result += fprintf(stream, " %4u | ", diagnosticLocation->lineNumber);

        do
            fputc(*(line++), stream);
        while (!isendln(*line));

        result += (int)(line - diagnosticLocation->line);

        if (diagnosticLocation->errorBegin)
        {
            uint16_t begin = diagnosticLocation->errorBegin, length = diagnosticLocation->errorLenght, position = diagnosticLocation->errorPosition, i = 0;

            result += fputs("\n      | ", stream);

            if (useColors)
                fputs("\x1B[1;32m", stream); // color: GREEN

            char c;

            for (; i < begin; i++, result++)
            {
                if (i == position)
                    c = '^';
                else
                    c = ' ';

                fputc(c, stream);
            }

            for (; i < (begin + length); i++, result++)
            {
                if (i == position)
                    c = '^';
                else
                    c = '~';

                fputc(c, stream);
            }

            for (; i < position; i++, result++)
            {
                if (i == position)
                    c = '^';
                else
                    c = ' ';

                fputc(c, stream);
            }

            if (useColors)
                fputs("\x1B[0m", stream); // color: RESET

            if (hint)
            {
                result += fputs("\n      | ", stream);

                if (useColors)
                    fputs("\x1B[1;32m", stream); // color: GREEN

                i = 0;

                while (i < position)
                    fputc(' ', stream), ++i;

                result += fputs(hint, stream);

                if (useColors)
                    fputs("\x1B[0m", stream); // color: RESET
            }
        }

        fputc('\n', stream), ++result;
    }

    return result;
}

CALC_API int CALC_STDCALL calcEmitDiagnostic(CalcDiagnostic_t *const diagnostic, FILE *const stream, bool_t useColors)
{
    int result = 0, code = diagnostic->code;

    CalcDiagnosticLevel_t level = diagnostic->level;
    CalcDiagnosticLocation_t *location = diagnostic->location;

    const char *message = (const char *)diagnostic->message, *color;

    if (location)
        result += calcEmitDiagnosticLocation(location, stream, useColors);

    fputc(' ', stream), ++result;

    if (useColors)
    {
        switch (level)
        {
        case CALC_DIAGNOSTIC_LEVEL_ERRNO:
            color = "\x1B[1;31m"; // color: RED
            break;

        case CALC_DIAGNOSTIC_LEVEL_NOTE:
            color = "\x1B[1;96m"; // color: BRIGHT CYAN
            break;

        case CALC_DIAGNOSTIC_LEVEL_WARNING:
            color = "\x1B[1;95m"; // color: BRIGHT MAGENTA
            break;

        case CALC_DIAGNOSTIC_LEVEL_ERROR:
        case CALC_DIAGNOSTIC_LEVEL_FATAL:
            color = "\x1B[1;91m"; // color: BRIGHT RED
            break;

        default:
            return unreach(), 0;
        }

        fputs(color, stream);
    }

    result += fputs(calcGetDiagnosticLevelName(level), stream);

    if (code)
    {
        fputc('[', stream), ++result;

#ifdef NOX_USE_YELLOW_FOR_ERRORS
         if (useColors)
            fputs("\x1B[1;93m", stream); // color: BRIGHT YELLOW
#endif // NOX_USE_YELLOW_FOR_ERRORS

        if (level == CALC_DIAGNOSTIC_LEVEL_ERRNO)
            result += fputs(errnoname(code), stream);
        else
            result += fprintf(stream, "CE%04d", code);

        if (useColors)
            fputs(color, stream);

        fputc(']', stream), ++result;
    }

    result += fputs(": ", stream);

    if (useColors)
        fputs("\x1B[1;97m", stream); // color: BRIGHT WHITE

    if (!message)
    {
        if (level == CALC_DIAGNOSTIC_LEVEL_ERRNO)
            message = strerror(code);
        else
            message = calcGetDiagnosticDefaultMessage(code);
    }

    result += fputs(message, stream);

    if (useColors)
        fputs("\x1B[0m", stream); // color: RESET

    fputc('\n', stream), ++result;

    if (location)
        result += calcEmitDiagnosticTrace(diagnostic->hint, location, stream, useColors);

    return result;
}

// Diagnostics Emitter

CALC_API CalcDiagnosticEmitter_t *CALC_STDCALL calcCreateDiagnosticEmitter(FILE *const errorStream, CalcDiagnosticEmitterFunc_t emitterFunction)
{
    CalcDiagnosticEmitter_t *emitter = alloc(CalcDiagnosticEmitter_t);

    emitter->stream = errorStream;
    emitter->emitter = emitterFunction ? emitterFunction : calcEmitDiagnostic;
    emitter->top = NULL;
    emitter->status = CALC_DIAGNOSTIC_EMITTER_STATUS_SUCCESS;
    emitter->warningCount = 0;
    emitter->errorCount = 0;
    emitter->useColors = FALSE;

    return emitter;
}

CALC_API CalcDiagnosticEmitter_t *CALC_STDCALL calcGetDefaultDiagnosticEmitter(void)
{
    static CalcDiagnosticEmitter_t *emitter = NULL;

    if (!emitter)
        emitter = calcCreateDiagnosticEmitter(stderr, NULL), emitter->useColors = TRUE;

    return emitter;
}

static inline CalcDiagnostic_t *CALC_STDCALL calc_DiagnosticEmitterGetBottom(CalcDiagnosticEmitter_t *const emitter)
{
    CalcDiagnostic_t *bottom = emitter->top;

    while (bottom && bottom->next)
        bottom = bottom->next;

    return bottom;
}

CALC_API CalcResult_t CALC_STDCALL calcDiagnosticEmitterPush(CalcDiagnosticEmitter_t *const emitter, CalcDiagnostic_t *const diagnostic)
{
    if (emitter->top)
        calc_DiagnosticEmitterGetBottom(emitter)->next = diagnostic;
    else
        emitter->top = diagnostic;

    CalcResult_t result = CALC_SUCCESS;

    switch (diagnostic->level)
    {
    case CALC_DIAGNOSTIC_LEVEL_NOTE:
        break;

    case CALC_DIAGNOSTIC_LEVEL_WARNING:
        emitter->warningCount++;
        break;

    case CALC_DIAGNOSTIC_LEVEL_ERROR:
    case CALC_DIAGNOSTIC_LEVEL_ERRNO:
        emitter->errorCount++;
        emitter->status = CALC_DIAGNOSTIC_EMITTER_STATUS_FAILURE;
        break;

    case CALC_DIAGNOSTIC_LEVEL_FATAL:
        emitter->errorCount++;
        emitter->status = CALC_DIAGNOSTIC_EMITTER_STATUS_ABORTED;

        result = CALC_FAILURE;

        break;

    default:
        unreach();
        break;
    }

    return result;
}

CALC_API int CALC_STDCALL calcDiagnosticEmitterEmit(CalcDiagnosticEmitter_t *const emitter)
{
    int result;

    if (emitter->top)
    {
        CalcDiagnostic_t *top = emitter->top;

        emitter->top = top->next;
        result = emitter->emitter(top, emitter->stream, emitter->useColors);

        calcDeleteDiagnostic(top);
    }
    else
    {
        result = 0;
    }

    return result;
}

CALC_API int CALC_STDCALL calcDiagnosticEmitterEmitAll(CalcDiagnosticEmitter_t *const emitter)
{
    int result = 0, i;

    for (i = 0; emitter->top; i++)
        result += calcDiagnosticEmitterEmit(emitter);

    return result;
}

CALC_API int CALC_STDCALL calcDiagnosticEmitterEpilogue(CalcDiagnosticEmitter_t *const emitter)
{
    int result = 0;
    FILE *stream = emitter->stream;

    calcDiagnosticEmitterEmitAll(emitter);

    result += fputs("\nProcess ", stream);

    switch (emitter->status)
    {
    case CALC_DIAGNOSTIC_EMITTER_STATUS_SUCCESS:
        result += fputs("exited", stream);
        break;

    case CALC_DIAGNOSTIC_EMITTER_STATUS_FAILURE:
        result += fputs("failed", stream);
        break;

    case CALC_DIAGNOSTIC_EMITTER_STATUS_ABORTED:
        result += fputs("faulted", stream);
        break;

    default:
        unreach();
        break;
    }

    uint16_t warnings = emitter->warningCount, errors = emitter->errorCount;

    result += fputs(" with ", stream);

    switch (warnings)
    {
    case 0:
        break;

    case 1:
        fprintf(stream, "%u warning and ", warnings);
        break;

    default:
        fprintf(stream, "%u warnings and ", warnings);
        break;
    }

    switch (errors)
    {
    case 0:
        break;

    case 1:
        fprintf(stream, "%u error", errors);
        break;

    default:
        fprintf(stream, "%u errors", errors);
        break;
    }

    result += fputs(".\n", stream);

    calcDeleteDiagnosticEmitter(emitter);

    return result;
}

CALC_API CalcResult_t CALC_STDCALL calcDiagnosticEmitterClear(CalcDiagnosticEmitter_t *const emitter)
{
    CalcResult_t result;

    if (emitter->top)
    {
        CalcDiagnostic_t *bottom = emitter->top;

        while (bottom && bottom->next)
            bottom = freeret(bottom, bottom->next);

        free(bottom);

        result = CALC_SUCCESS;
    }
    else
    {
        result = CALC_FAILURE;
    }

    return result;
}

CALC_API CalcResult_t CALC_STDCALL calcDiagnosticEmitterClose(CalcDiagnosticEmitter_t *const emitter)
{
    return (CalcResult_t)(!fclose(emitter->stream));
}

CALC_API void CALC_STDCALL calcDeleteDiagnosticEmitter(CalcDiagnosticEmitter_t *const emitter)
{
    calcDiagnosticEmitterClear(emitter);
    calcDiagnosticEmitterClose(emitter);

    free(emitter);

    return;
}
