#include "calc/base/string.h"
#include "calc/source/source_stream.h"

#include <time.h>

int main()
{
    CalcSourceStream_t *s = calcOpenSourceStream(CALC_CURRENT_PATH "/docs/examples/f.calc", FALSE, CALC_DEFAULT_ENCODING);

    int32_t t;

    double T1, T2, dT;

    T1 = (double)clock() / CLOCKS_PER_SEC;
    
    do
        t = calcSourceStreamRead(s);
    while (!istermn(calcSourceStreamPeek(s)));

    T2 = (double)clock() / CLOCKS_PER_SEC;

    dT = T2 - T1;

    printf("\nTime: %g ms\n", dT);

    calcDeleteSourceStream(s);
}
