#include "calc/source/source_stream.h"

int main()
{
    CalcSourceStream_t *s = calcOpenSourceStream(CALC_CURRENT_PATH "/docs/examples/f.calc", FALSE, CALC_DEFAULT_ENCODING);

    calcDeleteSourceStream(s);
}
