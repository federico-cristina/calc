#include "calc/core/sha256.h"

#include <stdio.h>

int main()
{
    const byte_t *bytes = (byte_t *)"Hello, world!\n";
    CalcSha256HashBlock_t output;
    
    calcSha256Encrypt(output, bytes, NULL);

    return 0;
}
