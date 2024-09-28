#include "calc/source/source_buffer.h"

CALC_API CalcSourceBuffer_t *CALC_STDCALL calcCreateSourceBuffer(size_t size, byte_t *const content, size_t count)
{
    CalcSourceBuffer_t *sourceBuffer = alloc(CalcSourceBuffer_t);

    if (!content || !count)
        sourceBuffer->data = dim(byte_t, size);
    else
        sourceBuffer->data = bufcpy(dim(byte_t, size), content, count);

    sourceBuffer->size = size;

    return sourceBuffer;
}

CALC_API CalcSourceBuffer_t *CALC_STDCALL calcCreateSourceBufferFromText(const char *const text)
{
    size_t length;

    if (!text)
        length = 0;
    else
        length = strlen(text);

    return calcCreateSourceBuffer(length + 1, (byte_t *)text, length);
}

CALC_API CalcSourceBuffer_t *CALC_STDCALL calcCreateSourceBufferFromFile(const char *const path)
{
    assert(path != NULL);

    FILE *stream = fopen(path, CALC_LOADMOD);

    if (!stream)
        return NULL;
    else
        return calcCreateSourceBufferFromStream(stream);
}

CALC_API CalcSourceBuffer_t *CALC_STDCALL calcCreateSourceBufferFromStream(FILE *const stream)
{
    assert(stream != NULL);

    size_t size = fgetsiz(stream);
    size_t fpos = 0;

    CalcSourceBuffer_t *sourceBuffer = calcCreateSourceBuffer(size, NULL, 0);

    byte_t *p = sourceBuffer->data;

    do
        fpos += fread(p + fpos, sizeof(byte_t), min(CALC_PAGESIZ, (size - fpos)), stream);
    while (fpos < size);

    p[fpos] = NUL;

    return sourceBuffer;
}

CALC_API CalcSourceBuffer_t *CALC_STDCALL calcCreateSourceBufferFromStdin(void)
{
    CalcSourceBuffer_t *sourceBuffer = calcCreateSourceBuffer(CALC_PAGESIZ, NULL, 0);

    char *buffer = fgets((char *)sourceBuffer->data, CALC_PAGESIZ, stdin), *newBuffer;
    size_t length = strlen(buffer);

    if (length < CALC_PAGESIZ)
    {
        newBuffer = (char *)realloc((void *)buffer, length + 1);

        if (newBuffer)
        {
            sourceBuffer->data = (byte_t *)newBuffer;
            sourceBuffer->size = length + 1;
        }
    }

    return sourceBuffer;
}

CALC_API int CALC_STDCALL calcDumpSourceBuffer(CalcSourceBuffer_t *const sourceBuffer, FILE *const stream)
{
    return fputs((const char *)sourceBuffer->data, !stream ? stdin : stream);
}

CALC_API void CALC_STDCALL calcDeleteSourceBuffer(CalcSourceBuffer_t *const sourceBuffer)
{
    free(sourceBuffer->data);
    free(sourceBuffer);

    return;
}
