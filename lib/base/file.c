#include "calc/base/file.h"

char *CALC_STDCALL fgetbase(char *const dest, const char *const path)
{
    char *p, *result;
    size_t i, lastSep = 0, lastDot = 0, size;

    for (p = (char *)path, i = 0; *p; p++, i++)
    {
        if (calcIsDirSep(*p))
            lastSep = i + 1;

        if (calcIsExtSep(*p))
            lastDot = i;
    }

    size = lastDot ? (lastDot - lastSep) : (i - lastSep);

    if (!dest)
        result = stralloc(size);
    else
        result = dest;

    return strncpy(result, (const char *)(path + lastSep), size);
}

size_t CALC_STDCALL fgetsiz(FILE *const stream)
{
    fpos_t fpos;

    if (fgetpos(stream, &fpos))
        failno("fgetpos is failed");

    if (fseek(stream, 0, SEEK_END))
        failno("fseek is failed");

#if CALC_PLATFORM_ID == CALC_PLATFORM_ID_WIN64
    size_t fsiz = _ftelli64(stream);
#else
    size_t fsiz = ftell(stream);
#endif

    if (fsetpos(stream, &fpos))
        failno("fsetpos is failed");

    return fsiz;
}
