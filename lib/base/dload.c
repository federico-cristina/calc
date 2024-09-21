#include "calc/base/dload.h"

#if CALC_PLATFORM_IS_WINDOWS
#   include <windows.h>
#else
#   include <dlfcn.h>
#endif

handle_t CALC_STDCALL dlload_current(void)
{
    static handle_t handle = NULL;

    if (!handle)
#if CALC_PLATFORM_IS_WINDOWS
        handle = (handle_t)GetModuleHandleA(NULL);
#else
        handle = (handle_t)dlopen(NULL, RTLD_LAZY);
#endif

    return handle;
}

handle_t CALC_STDCALL dlload(const char *const path)
{
    handle_t handle;

#if CALC_PLATFORM_IS_WINDOWS
    handle = (handle_t)LoadLibraryA((LPCSTR)path);
#else
    handle = (handle_t)dlopen(path, RTLD_LAZY);
#endif

    return handle;
}

handle_t CALC_STDCALL dlimpf(handle_t handle, const char *const name)
{
    handle_t func;

#if CALC_PLATFORM_IS_WINDOWS
    func = (handle_t)GetProcAddress((HMODULE)handle, (LPCSTR)name);
#else
    func = (handle_t)dlsymb((void *)lib, name);
#endif

    return func;
}

bool_t CALC_STDCALL dlunload(handle_t handle)
{
    bool_t result;

#if CALC_PLATFORM_IS_WINDOWS
    result = (bool_t)FreeLibrary((HMODULE)handle);
#else
    result = (bool_t)!dlclose((void *)handle);
#endif

    return result;
}
