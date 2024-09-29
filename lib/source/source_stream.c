#include "calc/source/source_stream.h"

static inline CalcSourceStream_t *CALC_STDCALL calc_InitializeSourceStream(CalcSourceStream_t *const sourceStream)
{
    sourceStream->path = NULL;
    sourceStream->stream = NULL;

    sourceStream->isStdin = FALSE;
    sourceStream->isText = FALSE;
    sourceStream->isOpen = FALSE;
    sourceStream->cleanup = FALSE;

    sourceStream->buffer = NULL;

    calcResetSourceLocation(&sourceStream->streamLocation);
    calcResetSourceLocation(&sourceStream->beginLocation);
    calcResetSourceLocation(&sourceStream->forwardLocation);

    return sourceStream;
}

static inline CalcSourceStream_t *CALC_STDCALL calc_CreateSourceStream(const char *const path, FILE *const stream, bool_t isStdin, bool_t isText, bool_t isOpen, bool_t cleanup, CalcSourceBuffer_t *const sourceBuffer)
{
    CalcSourceStream_t *sourceStream = alloc(CalcSourceStream_t);

    sourceStream->path = (char *)path;
    sourceStream->stream = stream;

    sourceStream->isStdin = isStdin;
    sourceStream->isText = isText;
    sourceStream->isOpen = isOpen;
    sourceStream->cleanup = cleanup;

    sourceStream->buffer = sourceBuffer;

    calcResetSourceLocation(&sourceStream->streamLocation);
    calcResetSourceLocation(&sourceStream->beginLocation);
    calcResetSourceLocation(&sourceStream->forwardLocation);

    return sourceStream;
}

CALC_API CalcSourceStream_t *CALC_STDCALL calcCreateSourceStreamFromText(const char *const text)
{
    return calc_CreateSourceStream(NULL, NULL, FALSE, TRUE, FALSE, FALSE, calcCreateSourceBufferFromText(text));
}

CALC_API CalcSourceStream_t *CALC_STDCALL calcCreateSourceStreamFromFile(const char *const path, bool_t cleanupPath)
{
    assert(path != NULL);

    CalcSourceBuffer_t *sourceBuffer = calcCreateSourceBufferFromFile(path);

    if (!sourceBuffer)
        return NULL;
    else
        return calc_CreateSourceStream(path, NULL, FALSE, FALSE, FALSE, cleanupPath, sourceBuffer);
}

CALC_API CalcSourceStream_t *CALC_STDCALL calcCreateSourceStreamFromStream(FILE *const stream)
{
    assert(stream != NULL);

    CalcSourceBuffer_t *sourceBuffer = calcCreateSourceBufferFromStream(stream);

    if (!sourceBuffer)
        return NULL;
    else
        return calc_CreateSourceStream(NULL, NULL, FALSE, FALSE, FALSE, FALSE, sourceBuffer);
}

CALC_API CalcSourceStream_t *CALC_STDCALL calcOpenSourceStream(const char *const path, bool_t cleanupPath)
{
    assert(path != NULL);

    FILE *stream = fopen(path, CALC_LOADMOD);

    if (!stream)
        return NULL;

    return calc_CreateSourceStream(path, stream, FALSE, FALSE, TRUE, cleanupPath, calcCreateSourceBuffer(CALC_PAGESIZ, NULL, 0));
}

CALC_API CalcSourceStream_t *CALC_STDCALL calcOpenStandardSourceStream(void)
{
    return calc_CreateSourceStream("<stdin>", stdin, TRUE, FALSE, TRUE, FALSE, calcCreateSourceBuffer(CALC_PAGESIZ, NULL, 0));
}

CALC_API bool_t CALC_STDCALL calcCloseSourceStream(CalcSourceStream_t *const sourceStream)
{
    if (sourceStream->isOpen)
        return sourceStream->isOpen = (bool_t)fclose(sourceStream->stream);
    else
        return FALSE;
}

CALC_API bool_t CALC_STDCALL calcClearSourceStream(CalcSourceStream_t *const sourceStream)
{
    return calcClearSourceBuffer(sourceStream->buffer);
}

CALC_API void CALC_STDCALL calcDeleteSourceStream(CalcSourceStream_t *const sourceStream)
{
    calcCloseSourceStream(sourceStream);
    calcDeleteSourceBuffer(sourceStream->buffer);

    if (sourceStream->cleanup)
        free(sourceStream->path);

    free(sourceStream);

    return;
}
