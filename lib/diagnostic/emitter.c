#include "calc/diagnostic/emitter.h"

CALC_API int CALC_STDCALL calcEmitDiagnosticLocation(CalcDiagnosticLocation_t *const diagnosticLocation, FILE *const stream)
{
    return fprintf(stream, "at %s in %s:%lu\n", diagnosticLocation->func, diagnosticLocation->file, diagnosticLocation->lineNumber);
}

static inline bool_t CALC_STDCALL calc_IsLineTerminator(int c)
{
    return (c != '\r') && (c != '\n') && (c != '\0');
}

CALC_API int CALC_STDCALL calcEmitDiagnosticTrace(CalcDiagnosticLocation_t *const diagnosticLocation, FILE *const stream)
{
    int result = 0;

    result += fputs(CALC_ERROR_TRACE_SPACES, stream);
    result += calcEmitDiagnosticLocation(diagnosticLocation, stream);

    char *line = diagnosticLocation->line;

    if (line)
    {
        uint32_t i = 0, length = diagnosticLocation->lineLength, l = diagnosticLocation->lineNumber;

        do
        {
            result += fprintf(stream, " %d | ", l++);

            while ((i < length) && calc_IsLineTerminator(line[i]))
                fputc(line[i++], stream);

            while ((i < length) && (line[i] == '\r'))
                ++i;

            fputc(line[i++], stream);
        } while (i < length);

        result += length;

        fputc('\n', stream);
    }

    return result;
}

CALC_API int CALC_STDCALL calcEmitDiagnostic(CalcDiagnostic_t *const diagnostic, FILE *const stream)
{
    int result = 0, level = diagnostic->level, code = diagnostic->code;

    if (level != CALC_DIAGNOSTIC_LEVEL_ERRNO)
    {
        const char *name;

        if (code)
        {
            switch (level)
            {
            case CALC_DIAGNOSTIC_LEVEL_NOTE:
                name = calcGetDiagnosticDisplayName(code);
                break;

            case CALC_DIAGNOSTIC_LEVEL_WARNING:
                name = calcGetDiagnosticDisplayName(code);
                break;

            case CALC_DIAGNOSTIC_LEVEL_ERROR:
            case CALC_DIAGNOSTIC_LEVEL_FATAL:
                name = calcGetDiagnosticDisplayName(code);
                break;

            default:
                return (int)unreach();
            }
        }
        else
        {
            name = calcGetDiagnosticLevel(level);
        }

        result += fprintf(stream, "%s: ", name);

        if (diagnostic->message)
        {
            result += fprintf(stream, "%s", diagnostic->message);
        }
        else
        {
            switch (level)
            {
            case CALC_DIAGNOSTIC_LEVEL_NOTE:
                result += fputs("something has been noted, but not specified", stream);
                break;

            case CALC_DIAGNOSTIC_LEVEL_WARNING:
                result += fputs("something that could potentially be an error has been reported, but I forgot what...", stream);
                break;

            case CALC_DIAGNOSTIC_LEVEL_ERROR:
                result += fputs("an error has been reported... but which??!", stream);
                break;

            case CALC_DIAGNOSTIC_LEVEL_FATAL:
                result += fputs("something killed the process, I wonder that was something very ugly!", stream);
                break;

            default:
                return unreach(), 0;
            }
        }
    }
    else
    {
        result += fprintf(stream, "errno %d (%s): ", code, errnoname(code));

        if (diagnostic->message)
            result += fprintf(stream, "%s (%s)", diagnostic->message, strerror(code));
        else
            result += fprintf(stream, "%s", strerror(code));
    }

    if (diagnostic->location)
        result += calcEmitDiagnosticTrace(diagnostic->location, stream);
    else
        fputc('\n', stream);

    return result + 1;
}

// Diagnostics Emitter

CALC_API CalcDiagnosticEmitter_t *CALC_STDCALL calcCreateDiagnosticEmitter(FILE *const errorStream, CalcDiagnosticEmitterFunc_t emitterFunction)
{
    CalcDiagnosticEmitter_t *emitter = alloc(CalcDiagnosticEmitter_t);

    emitter->stream = errorStream;
    emitter->emitter = emitterFunction ? emitterFunction : calcEmitDiagnostic;
    emitter->top = NULL;
    emitter->status = CALC_DIAGNOSTIC_EMITTER_STATUS_SUCCESS;
    emitter->noteCount = 0;
    emitter->warningCount = 0;
    emitter->errorCount = 0;

    return emitter;
}

static inline CalcDiagnostic_t *CALC_STDCALL calc_DiagnosticEmitterGetBottom(CalcDiagnosticEmitter_t *const emitter)
{
    CalcDiagnostic_t *bottom = emitter->top;

    while (bottom && bottom->next)
        bottom = bottom->next;

    return bottom;
}

CALC_API void CALC_STDCALL calcDiagnosticEmitterPush(CalcDiagnosticEmitter_t *const emitter, CalcDiagnostic_t *const diagnostic)
{
    if (emitter->top)
        calc_DiagnosticEmitterGetBottom(emitter)->next = diagnostic;
    else
        emitter->top = diagnostic;

    switch (diagnostic->level)
    {
    case CALC_DIAGNOSTIC_LEVEL_NOTE:
        ++emitter->noteCount;
        break;

    case CALC_DIAGNOSTIC_LEVEL_WARNING:
        ++emitter->warningCount;
        break;

    case CALC_DIAGNOSTIC_LEVEL_ERROR:
    case CALC_DIAGNOSTIC_LEVEL_ERRNO:
        ++emitter->errorCount;
        emitter->status = CALC_DIAGNOSTIC_EMITTER_STATUS_FAILURE;
        break;

    case CALC_DIAGNOSTIC_LEVEL_FATAL:
        ++emitter->errorCount;
        emitter->status = CALC_DIAGNOSTIC_EMITTER_STATUS_ABORTED;

        abort();

    default:
        unreach();
        return;
    }

    return;
}

CALC_API int CALC_STDCALL calcDiagnosticEmitterEmit(CalcDiagnosticEmitter_t *const emitter)
{
    int result;

    if (emitter->top)
    {
        CalcDiagnostic_t *top = emitter->top;

        emitter->top = top->next;
        result = emitter->emitter(top, emitter->stream);

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
        result += calcDiagnosticEmitterEmit(emitter), fputc('\n', emitter->stream), ++result;

    return result;
}

CALC_API int CALC_STDCALL calcDiagnosticEmitterEpilogue(CalcDiagnosticEmitter_t *const emitter)
{
    int result = 0;
    FILE *stream = emitter->stream;

    calcDiagnosticEmitterEmitAll(emitter);

    result += fputs("Process ", stream);

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
        return;
    }

    result += fprintf(stream, " with %u notes, %u warnings and %d errors.\n", emitter->noteCount, emitter->warningCount, emitter->errorCount);

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
