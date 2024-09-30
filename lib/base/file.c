#include "calc/base/error.h"
#include "calc/base/file.h"

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
