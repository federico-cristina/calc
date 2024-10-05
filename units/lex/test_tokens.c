#include "calc/lex/tokens.h"

#include <stdio.h>

int main()
{
    const char *lexeme = calcGetTokenLexeme(CALC_TOKEN_KEYWORD_TEMPLATE);

    printf("%s\n", lexeme);

    return 0;
}
