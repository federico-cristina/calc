#include "calc/base/error.h"

int handle(int value)
{
    return eprintfn("an error has been occurred: %d.", value), 1;
}

int main()
{
    jmp_buf buf;

    if (!jmpback(buf, handle))
        jump(32);

    return 0;
}
