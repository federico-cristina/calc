#include "calc/core/hash.h"

#include <stdio.h>

int main()
{
    const char *const text = "Hello, world!";

    CalcHashCode_t hash = calcGetBase64HashCode((const byte_t *)text);

    printf("%s -> %u\n", text, hash);

    return 0;
}