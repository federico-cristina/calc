#include "calc/lex/tokens.h"

CALC_API const char *CALC_STDCALL calcGetTokenLexeme(CalcTokenCode_t token)
{
    switch (token)
    {
    case CALC_TOKEN_INVALID:
        return "<\?>";

#pragma push_macro("calcDefineTokenWithLexeme")

#ifndef calcDefineTokenWithLexeme
    /// @brief Defines a token code using name parameter prefixed with
    ///        CALC_TOKEN_.
#   define calcDefineTokenWithLexeme(name, lexeme) \
    case name:                                     \
        return lexeme;
#endif // calcDefineTokenWithLexeme

#include CALC_LEX_TOKENS_INC_

#ifdef calcDefineTokenWithLexeme
#   undef calcDefineTokenWithLexeme
#endif // UNDEF calcDefineTokenWithLexeme

#pragma pop_macro("calcDefineTokenWithLexeme")

    default:
        return CALC_EMPTY_LEXEME;
    }
}
