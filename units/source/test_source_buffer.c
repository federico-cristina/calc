#include "calc/source/source_buffer.h"

int main()
{
    CalcSourceBuffer_t *s = calcCreateSourceBufferFromStdin();

    calcDumpSourceBuffer(s, stderr);

    calcDeleteSourceBuffer(s);

    return 0;
}
