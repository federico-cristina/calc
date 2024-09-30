#include "calc/base/string.h"

#include "calc/source/source_stream.h"

static inline CalcSourceStream_t *CALC_STDCALL calc_InitializeSourceStream(CalcSourceStream_t *const sourceStream)
{
    sourceStream->path = NULL;
    sourceStream->stream = NULL;

    sourceStream->isStdin = FALSE;
    sourceStream->isInitialized = FALSE;
    sourceStream->isOpen = FALSE;
    sourceStream->cleanup = FALSE;

    sourceStream->buffer = NULL;

    calcResetSourceLocation(&sourceStream->streamLocation);
    calcResetSourceLocation(&sourceStream->beginLocation);
    calcResetSourceLocation(&sourceStream->forwardLocation);

    return sourceStream;
}

static inline CalcSourceStream_t *CALC_STDCALL calc_CreateSourceStream(const char *const path, FILE *const stream, bool_t isStdin, bool_t isInitialized, bool_t isOpen, bool_t cleanup, CalcSourceEncoding_t encoding, CalcSourceBuffer_t *const sourceBuffer)
{
    CalcSourceStream_t *sourceStream = alloc(CalcSourceStream_t);

    sourceStream->path = (char *)path;
    sourceStream->stream = stream;

    sourceStream->isStdin = isStdin;
    sourceStream->isInitialized = isInitialized;
    sourceStream->isOpen = isOpen;
    sourceStream->cleanup = cleanup;

    sourceStream->encoding = encoding;
    sourceStream->buffer = sourceBuffer;

    calcResetSourceLocation(&sourceStream->streamLocation);
    calcResetSourceLocation(&sourceStream->beginLocation);
    calcResetSourceLocation(&sourceStream->forwardLocation);

    return sourceStream;
}

CALC_API CalcSourceStream_t *CALC_STDCALL calcCreateSourceStreamFromText(const char *const text, CalcSourceEncoding_t encoding)
{
    return calc_CreateSourceStream(NULL, NULL, FALSE, FALSE, FALSE, FALSE, encoding, calcCreateSourceBufferFromText(text));
}

CALC_API CalcSourceStream_t *CALC_STDCALL calcCreateSourceStreamFromFile(const char *const path, bool_t cleanupPath, CalcSourceEncoding_t encoding)
{
    assert(path != NULL);

    CalcSourceBuffer_t *sourceBuffer = calcCreateSourceBufferFromFile(path);

    if (!sourceBuffer)
        return NULL;
    else
        return calc_CreateSourceStream(path, NULL, FALSE, FALSE, FALSE, cleanupPath, encoding, sourceBuffer);
}

CALC_API CalcSourceStream_t *CALC_STDCALL calcCreateSourceStreamFromStream(FILE *const stream, CalcSourceEncoding_t encoding)
{
    assert(stream != NULL);

    CalcSourceBuffer_t *sourceBuffer = calcCreateSourceBufferFromStream(stream);

    if (!sourceBuffer)
        return NULL;
    else
        return calc_CreateSourceStream(NULL, NULL, FALSE, FALSE, FALSE, FALSE, encoding, sourceBuffer);
}

CALC_API CalcSourceStream_t *CALC_STDCALL calcOpenSourceStream(const char *const path, bool_t cleanupPath, CalcSourceEncoding_t encoding)
{
    assert(path != NULL);

    FILE *stream = fopen(path, CALC_LOADMOD);

    if (!stream)
        return NULL;

    return calc_CreateSourceStream(path, stream, FALSE, FALSE, TRUE, cleanupPath, encoding, calcCreateSourceBuffer(CALC_PAGESIZ, NULL, 0));
}

CALC_API CalcSourceStream_t *CALC_STDCALL calcOpenStandardSourceStream(void)
{
    return calc_CreateSourceStream("<stdin>", stdin, TRUE, FALSE, TRUE, FALSE, CALC_DEFAULT_ENCODING, calcCreateSourceBuffer(CALC_PAGESIZ, NULL, 0));
}

static inline bool_t CALC_STDCALL calc_SourceStreamNeedsARefill(CalcSourceStream_t *const sourceStream, uint32_t offset)
{
    return !sourceStream->isInitialized || ((sourceStream->forwardLocation.ch + offset) >= sourceStream->buffer->size);
}

static inline bool_t CALC_STDCALL calc_SourceStreamRefill(CalcSourceStream_t *const sourceStream)
{
    if (!sourceStream->isOpen || !sourceStream->stream)
        return FALSE;

    FILE *stream = sourceStream->stream;
    byte_t *data = sourceStream->buffer->data;
    size_t begin = sourceStream->beginLocation.ch, count = sourceStream->buffer->size - begin;

    if (feof(stream))
        return FALSE;

    if (begin)
        bufmov(data, (data + begin), count);

    if (!sourceStream->isStdin)
        fread((void *)(data + begin), sizeof(byte_t), count, stream);
    else
        fgets((char *)(data + begin), count, stream);

    if (!sourceStream->isInitialized)
    {
        sourceStream->isInitialized = TRUE;
    }
    else
    {
        CalcSourceLocation_t *beginLoc = &sourceStream->beginLocation, *forwardLoc = &sourceStream->forwardLocation;

        if (begin)
            calcSetSourceLocation(forwardLoc, forwardLoc->ch - beginLoc->ch, forwardLoc->co - beginLoc->co, forwardLoc->ln - beginLoc->ln);
        else
            calcResetSourceLocation(forwardLoc);

        calcResetSourceLocation(beginLoc);
    }

    return TRUE;
}

CALC_API int32_t CALC_STDCALL calcSourceStreamPeek(CalcSourceStream_t *const sourceStream)
{
    if (calc_SourceStreamNeedsARefill(sourceStream, 0) && !calc_SourceStreamRefill(sourceStream))
        return EOF;
    else
        return calcSourceBufferGetChar(sourceStream->buffer, sourceStream->encoding, sourceStream->forwardLocation.ch, NULL);
}

static inline int32_t CALC_STDCALL calc_SourceStreamRead(CalcSourceStream_t *const sourceStream, ssize_t *const outOffset)
{
    if (calc_SourceStreamNeedsARefill(sourceStream, 0) && !calc_SourceStreamRefill(sourceStream))
        return EOF;

    int32_t result;
    ssize_t offset;

    result = calcSourceBufferGetChar(sourceStream->buffer, sourceStream->encoding, sourceStream->forwardLocation.ch, &offset);

    switch (result)
    {
    case EOF:
    case NUL:
        break;

    case EOL:
        sourceStream->streamLocation.co = 0;
        sourceStream->streamLocation.ln++;
        sourceStream->forwardLocation.co = 0;
        sourceStream->forwardLocation.ln++;
        break;

    default:
        sourceStream->streamLocation.co += offset;
        sourceStream->forwardLocation.co += offset;
        break;
    }

    sourceStream->streamLocation.ch += offset;
    sourceStream->forwardLocation.ch += offset;

    if (outOffset && *outOffset)
        *outOffset = offset;

    return result;
}

CALC_API int32_t CALC_STDCALL calcSourceStreamRead(CalcSourceStream_t *const sourceStream)
{
    return calc_SourceStreamRead(sourceStream, NULL);
}

CALC_API int32_t CALC_STDCALL calcSourceStreamPeekOffset(CalcSourceStream_t *const sourceStream, uint32_t offset)
{
    return calcSourceBufferGetChar(sourceStream->buffer, sourceStream->encoding, sourceStream->forwardLocation.ch + offset, NULL);
}

CALC_API int32_t CALC_STDCALL calcSourceStreamReadOffset(CalcSourceStream_t *const sourceStream, uint32_t offset)
{
    if (calc_SourceStreamNeedsARefill(sourceStream, offset) && !calc_SourceStreamRefill(sourceStream))
        return EOF;

    int32_t result = EOF;
    uint32_t i;

    for (i = 0; i < offset; i++)
        result = calcSourceStreamRead(sourceStream);

    return result;
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
