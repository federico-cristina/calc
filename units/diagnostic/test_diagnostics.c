#include "calc/diagnostic/emitter.h"

int main()
{
    CalcDiagnosticEmitter_t *e = calcGetDefaultDiagnosticEmitter();

    calcDiagnosticEmitterReport(e, CALC_DIAGNOSTIC_LEVEL_ERROR, CALC_DIAGNOSTIC_CODE_CE0001, calcCreateDiagnosticLocation("main.c", "main", "    x + 1\r\n", 5, 9, 1, 9), "expected ';' after expression", FALSE, ";", FALSE);
    calcDiagnosticEmitterEpilogue(e);

    return 0;
}
