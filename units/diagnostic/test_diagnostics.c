#include "calc/diagnostic/emitter.h"

int main()
{
    calcSuppressDiagnostic(CALC_DIAGNOSTIC_CODE_E0001);

    CalcDiagnosticEmitter_t *e = calcGetDefaultDiagnosticEmitter();

    e->emitSuppressedDiagnostics = TRUE;

    calcDiagnosticEmitterReport(e, CALC_DIAGNOSTIC_CODE_E0001, calcCreateDiagnosticLocation("main.c", "main", "    x + 1\r\n", 5, 9, 1, 9), "expected ';' after expression", FALSE, ";", FALSE);
    calcDiagnosticEmitterEpilogue(e);

    return 0;
}
