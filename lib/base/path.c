#include "calc/base/path.h"
#include "calc/base/string.h"

static size_t CALC_STDCALL _path_getlastsep(const char *const path, size_t *const outLength)
{
    char *p;
    size_t i, lastSep = 0;

    for (p = (char *)path, i = 0; (*p && (*p != CALC_PATHSEP)); p++, i++)
    {
        if (calcIsDirSep(*p))
            lastSep = i + 1;
    }

    if (outLength && *outLength)
        *outLength = i;

    return lastSep;
}

char *CALC_STDCALL path_getroot(char *const dest, const char *const path)
{
    if (!path)
        return dest;
    else
        return strnmov(dest, path, _path_getlastsep(path, NULL));
}

char *CALC_STDCALL path_getname(char *const dest, const char *const path)
{
    if (!path)
        return dest;

    size_t lastSep, length;

    lastSep = _path_getlastsep(path, &length);

    return strnmov(dest, (const char *)(path + lastSep), length - lastSep);
}

char *CALC_STDCALL path_getextn(char *const dest, const char *const path)
{
    if (!path)
        return dest;

    char *p, *result;
    size_t i, lastDot = 0, size;

    for (p = (char *)path, i = 0; (*p && (*p != CALC_PATHSEP)); p++, i++)
    {
        if (calcIsExtSep(*p))
            lastDot = i;
    }

    if (!lastDot)
        return NULL;
    else
        return strnmov(dest, (const char *)(path + lastDot), i);
}

char *CALC_STDCALL path_getbase(char *const dest, const char *const path)
{
    if (!path)
        return dest;

    char *p, *result;
    size_t i, lastSep = 0, lastDot = 0, size;

    for (p = (char *)path, i = 0; (*p && (*p != CALC_PATHSEP)); p++, i++)
    {
        if (calcIsDirSep(*p))
            lastSep = i + 1;

        if (calcIsExtSep(*p))
            lastDot = i;
    }

    return strnmov(dest, (const char *)(path + lastSep), lastDot ? (lastDot - lastSep) : (i - lastSep));
}
