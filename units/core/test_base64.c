#include "calc/core/base64.h"

#include <stdio.h>

int main()
{
    const byte_t *bytes = (const byte_t *)"Hello, world!\n";
    byte_t output[4096] = { 0 };

    calcBase64Encode(bytes, output, buflen(bytes), TRUE);

    printf("%s -> %s\n", (char *)bytes, (char *)output);

    return 0;
}
