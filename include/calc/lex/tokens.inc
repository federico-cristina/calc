/**
 * @file        tokens.inc
 *
 * @author      Federico Cristina <federico.cristina@outlook.it>
 *
 * @copyright   Copyright (c) 2024 Federico Cristina
 *
 *              This file is part of the calc scripting language project,
 *              under the Apache License v2.0. See LICENSE for license
 *              informations.
 *
 * @brief       This file is an x-macro header file, designed to be
 *              included more than once. Its use can change depending
 *              how is defined the corresponed x-macro.
 * 
 *              In this x-macro file are defined token informations.
 */

#ifndef CALC_EMPTY_LEXEME
#   ifdef NULL
 /// @brief Represents an empty lexeme.
#       define CALC_EMPTY_LEXEME NULL
#   else
 /// @brief Represents an empty lexeme.
#       define CALC_EMPTY_LEXEME ((void *)0x00)
#   endif
#endif // CALC_EMPTY_LEXEME

#ifndef calcDefineToken
/// @brief This is a placeholder macro for an external definition,
///        actually this is empty.
#   define calcDefineToken(name, lexeme)
#endif // calcDefineToken

 /* =---- Trivial Tokens ----------------------------------------= */

#ifndef calcDefineTrivialToken
/// @brief This macro defines a trivial token code, a token without a
///        specified lexeme that will be treated as information about
///        the source stream.
#   define calcDefineTrivialToken(name) calcDefineToken(name, CALC_EMPTY_LEXEME)
#endif // calcDefineTrivialToken

// Positional Tokens

/// @brief 'eof' positional trivia token.
calcDefineTrivialToken(CALC_TOKEN_TRIVIAL_ENDOF)
/// @brief 'eol' positional trivia token, reports to the lexer that the
///        current logical line is ended. 
calcDefineTrivialToken(CALC_TOKEN_TRIVIAL_ENDOL)
/// @brief 'nul' positional trivia token, reports to the lexer that the
///        sequence is terminated, but not the logical line; so if the
///        source stream is interactive will be requested to insert a new
///        line of code. 
calcDefineTrivialToken(CALC_TOKEN_TRIVIAL_NULCH)

// Other Tokens

/// @brief Removed line trivial token, reports to the lexer that the current
///        must be ignored, like comments.
calcDefineTrivialToken(CALC_TOKEN_TRIVIAL_REMLN)

#ifdef calcDefineTrivialToken
#   undef calcDefineTrivialToken
#endif // UNDEF calcDefineTrivialToken

/* =---- Keyword Tokens ----------------------------------------= */

// Global-Context Keyword Tokens

#ifndef calcDefineKeywordToken
/// @brief This macro defines a keyword token code, a token with a specific
///        lexeme that is reserved and is used to build statements.
#   define calcDefineKeywordToken(name, lexeme) calcDefineToken(name, lexeme)
#endif // calcDefineKeywordToken

/* NOTE: Keep the number of keywords between 48 and 56. Context-specific
 *       keywords (or contextual reserved words) will be inserted and
 *       removed (generally, managed) by the lexer with becktracks from
 *       the parser.
 */

/// @brief 'async' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_ASYNC,            "async")
/// @brief 'auto' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_AUTO,             "auto")
/// @brief 'await' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_AWAIT,            "await")
/// @brief 'bool' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_BOOLEAN,          "bool")
/// @brief 'break' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_BREAK,            "break")
/// @brief 'case' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_CASE,             "case")
/// @brief 'catch' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_CATCH,            "catch")
/// @brief 'char' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_CHAR,             "char")
/// @brief 'const' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_CONSTANT,         "const")
/// @brief 'continue' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_CONTINUE,         "continue")
/// @brief 'default' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_DEFAULT,          "default")
/// @brief 'do' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_DO,               "do")
/// @brief 'else' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_ELSE,             "else")
/// @brief 'extern' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_EXTERN,           "extern")
/// @brief 'enum' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_ENUM,             "enum")
/// @brief 'false' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_FALSE,            "false")
/// @brief 'float' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_FLOAT,            "float")
/// @brief 'fn' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_FUNCTION,         "fn")
/// @brief 'for' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_FOR,              "for")
/// @brief 'goto' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_GOTO,             "goto")
/// @brief 'if' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_IF,               "if")
/// @brief 'int' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_INT,              "int")
/// @brief 'impl' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_IMPLEMENT,        "impl")
/// @brief 'let' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_LET,              "let")
/// @brief 'macro' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_MACRO,            "macro")
/// @brief 'match' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_MATCH,            "match")
/// @brief 'model' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_MODEL,            "model")
/// @brief 'module' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_MODULE,           "module")
/// @brief 'nameof' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_NAMEOF,           "nameof")
/// @brief 'object' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_OBJECT,           "object")
/// @brief 'pub' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_PUBLIC,           "pub")
/// @brief 'return' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_RETURN,           "return")
/// @brief 'sizeof' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_SIZEOF,           "sizeof")
/// @brief 'static' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_STATIC,           "static")
/// @brief 'struct' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_STRUCT,           "struct")
/// @brief 'switch' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_SWITCH,           "switch")
/// @brief 'templ' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_TEMPLATE,         "templ")
/// @brief 'throw' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_THROW,            "throw")
/// @brief 'true' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_TRUE,             "true")
/// @brief 'try' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_TRY,              "try")
/// @brief 'typeof' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_TYPEOF,           "typeof")
/// @brief 'unsigned' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_UNION,            "union")
/// @brief 'use' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_UNSIGNED,         "unsigned")
/// @brief 'use' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_USE,              "use")
/// @brief 'var' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_VARIABLE,         "var")
/// @brief 'var' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_VOID,             "void")
/// @brief 'while' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_WHILE,            "while")
/// @brief 'yield' keyword token code.
calcDefineKeywordToken(CALC_TOKEN_KEYWORD_YIELD,            "yield")

#ifndef CALC_TOKEN_COUNT_OF_KEYWORDS
/// @brief Specifies if keywords are alphabetically sorted.
#   define CALC_TOKEN_COUNT_OF_KEYWORDS (CALC_TOKEN_KEYWORD_YIELD - CALC_TOKEN_KEYWORD_ASYNC + 1)
#endif // CALC_TOKEN_COUNT_OF_KEYWORDS

#ifdef calcDefineKeywordToken
#   undef calcDefineKeywordToken
#endif // UNDEF calcDefineKeywordToken

// Object-Context Keyword Tokens

#ifndef calcDefineObjectKeywordToken
/// @brief This macro defines a keyword token code that will be used
///        only in the object (class) context.
#   define calcDefineObjectKeywordToken(name, lexeme) calcDefineToken(name, lexeme)
#endif // calcDefineObjectKeywordToken

/// @brief 'abstract' keyword token code.
calcDefineObjectKeywordToken(CALC_TOKEN_KEYWORD_ABSTRACT,   "abstract")
/// @brief 'base' keyword token code.
calcDefineObjectKeywordToken(CALC_TOKEN_KEYWORD_BASE,       "base")
/// @brief 'final' keyword token code.
calcDefineObjectKeywordToken(CALC_TOKEN_KEYWORD_FINAL,      "final")
/// @brief 'method' keyword token code.
calcDefineObjectKeywordToken(CALC_TOKEN_KEYWORD_METHOD,     "method")
/// @brief 'op' keyword token code.
calcDefineObjectKeywordToken(CALC_TOKEN_KEYWORD_OPERATOR,   "op")
/// @brief 'override' keyword token code.
calcDefineObjectKeywordToken(CALC_TOKEN_KEYWORD_OPERATOR,   "override")
/// @brief 'priv' keyword token code.
calcDefineObjectKeywordToken(CALC_TOKEN_KEYWORD_PRIVATE,    "priv")
/// @brief 'prop' keyword token code.
calcDefineObjectKeywordToken(CALC_TOKEN_KEYWORD_PROPERTY,   "prop")
/// @brief 'prot' keyword token code.
calcDefineObjectKeywordToken(CALC_TOKEN_KEYWORD_PROTECTED,  "prot")
/// @brief 'this' keyword token code.
calcDefineObjectKeywordToken(CALC_TOKEN_KEYWORD_THIS,       "this")
/// @brief 'virtual' keyword token code.
calcDefineObjectKeywordToken(CALC_TOKEN_KEYWORD_VIRTUAL,    "virtual")

#ifndef CALC_TOKEN_COUNT_OF_OBJECT_KEYWORDS
/// @brief Specifies if keywords are alphabetically sorted.
#   define CALC_TOKEN_COUNT_OF_OBJECT_KEYWORDS (CALC_TOKEN_KEYWORD_VIRTUAL - CALC_TOKEN_KEYWORD_ABSTRACT + 1)
#endif // CALC_TOKEN_COUNT_OF_OBJECT_KEYWORDS

#ifdef calcDefineObjectKeywordToken
#   undef calcDefineObjectKeywordToken
#endif // UNDEF calcDefineObjectKeywordToken

// Property-Context Keyword Tokens

#ifndef calcDefinePropertyKeywordToken
/// @brief This macro defines a keyword token code that will be used
///        only in the object's property context.
#   define calcDefinePropertyKeywordToken(name, lexeme) calcDefineToken(name, lexeme)
#endif // calcDefinePropertyKeywordToken

/// @brief 'get' property keyword token code.
calcDefinePropertyKeywordToken(CALC_TOKEN_KEYWORD_GET,      "get")
/// @brief 'init' property keyword token code.
calcDefinePropertyKeywordToken(CALC_TOKEN_KEYWORD_INIT,     "init")
/// @brief 'set' property keyword token code.
calcDefinePropertyKeywordToken(CALC_TOKEN_KEYWORD_SET,      "set")

#ifndef CALC_TOKEN_COUNT_OF_PROPERTY_KEYWORDS
/// @brief Specifies if keywords are alphabetically sorted.
#   define CALC_TOKEN_COUNT_OF_PROPERTY_KEYWORDS (CALC_TOKEN_KEYWORD_SET - CALC_TOKEN_KEYWORD_GET + 1)
#endif // CALC_TOKEN_COUNT_OF_PROPERTY_KEYWORDS

#ifdef calcDefinePropertyKeywordToken
#   undef calcDefinePropertyKeywordToken
#endif // UNDEF calcDefinePropertyKeywordToken

// Directive-Context Keyword Tokens

#ifndef calcDefineDirectiveKeywordToken
/// @brief This macro defines a keyword token code that will be used
///        only in the object (class) context.
#   define calcDefineDirectiveKeywordToken(name, lexeme) calcDefineToken(name, lexeme)
#endif // calcDefineDirectiveKeywordToken

/// @brief 'get' property keyword token code.
calcDefineDirectiveKeywordToken(CALC_TOKEN_KEYWORD_DEFINED, "defined")
/// @brief 'set' property keyword token code.
calcDefineDirectiveKeywordToken(CALC_TOKEN_KEYWORD_EXISTS,  "exists")

#ifndef CALC_TOKEN_COUNT_OF_DIRECTIVE_KEYWORDS
/// @brief Specifies if keywords are alphabetically sorted.
#   define CALC_TOKEN_COUNT_OF_DIRECTIVE_KEYWORDS (CALC_TOKEN_KEYWORD_EXISTS - CALC_TOKEN_KEYWORD_DEFINED + 1)
#endif // CALC_TOKEN_COUNT_OF_DIRECTIVE_KEYWORDS

#ifdef calcDefineDirectiveKeywordToken
#   undef calcDefineDirectiveKeywordToken
#endif // UNDEF calcDefineDirectiveKeywordToken

/* =---- Directive Tokens --------------------------------------= */

#ifndef calcDefineDirectiveToken
/// @brief This macro defines a directive token code.
#   define calcDefineDirectiveToken(name, lexeme) calcDefineToken(name, lexeme)
#endif // calcDefineDirectiveToken

/// @brief 'case' directive token code.
calcDefineDirectiveToken(CALC_TOKEN_DIRECTIVE_CASE,         "case")
/// @brief 'define' directive token code.
calcDefineDirectiveToken(CALC_TOKEN_DIRECTIVE_DEFINE,       "define")
/// @brief 'elif' directive token code.
calcDefineDirectiveToken(CALC_TOKEN_DIRECTIVE_ELIF,         "elif")
/// @brief 'elifdef' directive token code.
calcDefineDirectiveToken(CALC_TOKEN_DIRECTIVE_ELIFDEF,      "elifdef")
/// @brief 'elifndef' directive token code.
calcDefineDirectiveToken(CALC_TOKEN_DIRECTIVE_ELIFNDEF,     "elifndef")
/// @brief 'else' directive token code.
calcDefineDirectiveToken(CALC_TOKEN_DIRECTIVE_ELSE,         "else")
/// @brief 'endif' directive token code.
calcDefineDirectiveToken(CALC_TOKEN_DIRECTIVE_ENDIF,        "endif")
/// @brief 'endswitch' directive token code.
calcDefineDirectiveToken(CALC_TOKEN_DIRECTIVE_ENDSWITCH,    "endswitch")
/// @brief 'error' directive token code.
calcDefineDirectiveToken(CALC_TOKEN_DIRECTIVE_ERROR,        "error")
/// @brief 'if' directive token code.
calcDefineDirectiveToken(CALC_TOKEN_DIRECTIVE_IF,           "if")
/// @brief 'ifdef' directive token code.
calcDefineDirectiveToken(CALC_TOKEN_DIRECTIVE_IFDEF,        "ifdef")
/// @brief 'ifndef' directive token code.
calcDefineDirectiveToken(CALC_TOKEN_DIRECTIVE_IFNDEF,       "ifndef")
/// @brief 'include' directive token code.
calcDefineDirectiveToken(CALC_TOKEN_DIRECTIVE_INCLUDE,      "include")
/// @brief 'line' directive token code.
calcDefineDirectiveToken(CALC_TOKEN_DIRECTIVE_LINE,         "line")
/// @brief 'load' directive token code.
calcDefineDirectiveToken(CALC_TOKEN_DIRECTIVE_LOAD,         "load")
/// @brief 'pragma' directive token code.
calcDefineDirectiveToken(CALC_TOKEN_DIRECTIVE_PRAGMA,       "pragma")
/// @brief 'switch' directive token code.
calcDefineDirectiveToken(CALC_TOKEN_DIRECTIVE_SWITCH,       "switch")
/// @brief 'undef' directive token code.
calcDefineDirectiveToken(CALC_TOKEN_DIRECTIVE_UNDEF,        "undef")

#ifndef CALC_TOKEN_COUNT_OF_DIRECTIVES
/// @brief Specifies if keywords are alphabetically sorted.
#   define CALC_TOKEN_COUNT_OF_DIRECTIVES (CALC_TOKEN_DIRECTIVE_UNDEF - CALC_TOKEN_DIRECTIVE_CASE + 1)
#endif // CALC_TOKEN_COUNT_OF_DIRECTIVES

#ifdef calcDefineDirectiveToken
#   undef calcDefineDirectiveToken
#endif // UNDEF calcDefineDirectiveToken

/* =---- Literal Tokens ----------------------------------------= */

#ifndef calcDefineLiteralToken
/// @brief This macro defines a literal contant token code that will be
///        used to represents value lexemes.
#   define calcDefineLiteralToken(name) calcDefineToken(name, CALC_EMPTY_LEXEME)
#endif // calcDefineLiteralToken

/// @brief Literal identifier token code.
calcDefineLiteralToken(TOK_IDENT)
/// @brief Literal identifier or keyword token code.
calcDefineLiteralToken(TOK_IDENT_OR_KWORD)

// Numeric Literals

/* NOTE: Some tokens, like integer literals have subcategories, this
 *       serves to provide a reduction operation between lexical and
 *       syntactic analysis. This reduction operation constist in a
 *       translation of the subcategorized lexeme to a form that matches
 *       the category lexeme.
 * 
 *       For example, a token with code CALC_TOKEN_LITERAL_INTEGER_BIN may
 *       have a lexeme like '0b0101' that can be reduced to integral number
 *       '5'. This transformation can optimize parsing phase and type
 *       checking.
 */

/// @brief Integer literal constant token code.
calcDefineLiteralToken(CALC_TOKEN_LITERAL_INTEGER)

/// @brief Binary integer literal constant token code.
calcDefineLiteralToken(CALC_TOKEN_LITERAL_INTEGER_BIN       /* [0][Bb][01]+ */)
/// @brief Octal integer literal constant token code.
calcDefineLiteralToken(CALC_TOKEN_LITERAL_INTEGER_OCT       /* [0][Cc][0-7]+ */)
/// @brief Decimal integer literal constant token code.
calcDefineLiteralToken(CALC_TOKEN_LITERAL_INTEGER_DEC       /* ([0][Dd])?[0-9]+ */)
/// @brief Hexadecimal integer literal constant token code.
calcDefineLiteralToken(CALC_TOKEN_LITERAL_INTEGER_HEX       /* [0][Xx][0-9a-fA-F]+ */)

/// @brief Floating point literal constant token code. 
calcDefineLiteralToken(CALC_TOKEN_LITERAL_FLOAT)

/// @brief Binary floating point literal constant token code. 
calcDefineLiteralToken(CALC_TOKEN_LITERAL_FLOAT_BIN         /* [0][Bb][01]*[.][01]+ */)
/// @brief Octal floating point literal constant token code. 
calcDefineLiteralToken(CALC_TOKEN_LITERAL_FLOAT_OCT         /* [0][Cc][0-7]*[.][0-7]+ */)
/// @brief Decimal floating point literal constant token code. 
calcDefineLiteralToken(CALC_TOKEN_LITERAL_FLOAT_DEC         /* ([0][Dd])?[0-9]*[.][0-9]+ */)
/// @brief Hexadecimal floating point literal constant token code. 
calcDefineLiteralToken(CALC_TOKEN_LITERAL_FLOAT_HEX         /* [0][Xx][0-9a-fA-F]*[.][0-9a-fA-F]+ */)

// Textual Literals

/// @brief Character literal constant token code.
calcDefineLiteralToken(CALC_TOKEN_LITERAL_CHAR)

/// @brief Character escape sequence literal constant token code.
calcDefineLiteralToken(CALC_TOKEN_LITERAL_CHAR_ESC          /* ['][\][abefnrstv\?'"]['] */) 
/// @brief Octal code point literal constant token code.
calcDefineLiteralToken(CALC_TOKEN_LITERAL_CHAR_OCT          /* ['][\][0-7]{1,3}['] */)
/// @brief Hexadecimal code point literal constant token code.
calcDefineLiteralToken(CALC_TOKEN_LITERAL_CHAR_HEX          /* ['][\][Xx][0-9a-fA-F]{1,4}['] */)
/// @brief Unicode code point literal constant token code.
calcDefineLiteralToken(CALC_TOKEN_LITERAL_CHAR_UNI          /* ['][\][Uu][0-9a-fA-F]{1,6}['] */)

/// @brief Character string literal constant token code.
calcDefineLiteralToken(CALC_TOKEN_LITERAL_STRING)

#ifdef calcDefineLiteralToken
#   undef calcDefineLiteralToken
#endif // UNDEF calcDefineLiteralToken

/* =---- Punctuation Tokens ------------------------------------= */

#ifndef calcDefinePunctorToken
/// @brief This macro defines a punctuator token code.
#   define calcDefinePunctorToken(name, lexeme) calcDefineToken(name, lexeme)
#endif // calcDefinePunctorToken

// Bracket Punctuators

/// @brief '()' bracket punctuator token code.
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_ROUND,            "()")

/// @brief '(' bracket punctuator token code.
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_ROUND_L,          "(")
/// @brief ')' bracket punctuator token code.
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_ROUND_R,          ")")

/// @brief '[]' bracket punctuator token code.
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_SQUAR,            "[]")

/// @brief '[' bracket punctuator token code.
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_SQUAR_L,          "[")
/// @brief ']' bracket punctuator token code.
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_SQUAR_R,          "]")

/// @brief '{}' bracket punctuator token code.
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_CURLY,            "{}")

/// @brief '{' bracket punctuator token code.
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_CURLY_L,          "{")
/// @brief '}' bracket punctuator token code.
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_CURLY_R,          "}")

#ifndef noxTokenCodeIsBrackPunct
/// @brief Checks if token t is a bracket token.
#   define noxTokenCodeIsBrackPunct(t) (((t) >= CALC_TOKEN_PUNCTOR_ROUND) && ((t) <= CALC_TOKEN_PUNCTOR_CURLY_R))
#endif // noxTokenCodeIsBrackPunct

// Stray punctuators

/// @brief '~' stray punctuator token code. (tilde)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_TILDE,            "~")

/// @brief '?' stray punctuator token code. (question mark)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_QUEST,            "?")
/// @brief '!' stray punctuator token code. (exclamation mark)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_EXCLM,            "!")
/// @brief '&' stray punctuator token code. (ampersand)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_AMPER,            "&")
/// @brief '|' stray punctuator token code. (pipe)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_PIPEE,            "|")
/// @brief '^' stray punctuator token code. (caret)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_CARET,            "^")

/// @brief '<' stray punctuator token code. (less than)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_LESST,            "<")
/// @brief '>' stray punctuator token code. (greater than)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_GREAT,            ">")
/// @brief '=' stray punctuator token code. (equal)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_EQUAL,            "=")

/// @brief '+' stray punctuator token code. (plus)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_PLUSS,            "+")
/// @brief '-' stray punctuator token code. (minus)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_MINUS,            "-")
/// @brief '*' stray punctuator token code. (asterisk)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_STARR,            "*")
/// @brief '/' stray punctuator token code. (slash)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_SLASH,            "/")
/// @brief '%' stray punctuator token code. (percent)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_PERCN,            "%")

/// @brief '#' stray punctuator token code. (hash)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_SHARP,            "#")
/// @brief '@' stray punctuator token code. (at)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_ATSIG,            "@")

/// @brief ',' stray punctuator token code. (comma)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_COMMA,            ",")
/// @brief '.' stray punctuator token code. (dot)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_POINT,            ".")
/// @brief ':' stray punctuator token code. (colon)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_COLON,            ":")
/// @brief ';' stray punctuator token code. (semicolon)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_SEMIC,            ";")

/// @brief '\' stray punctuator token code. (backslash)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_BACKS,            "\\")
/// @brief '`' stray punctuator token code. (backtick)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_BACKT,            "`")

// Compound punctuators -- Doubled

/// @brief '??' compound punctuator token code. (double question mark)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_QUEST_QUEST,      "??")
/// @brief '!!' compound punctuator token code. (double exclamation mark)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_EXCLM_EXCLM,      "!!")
/// @brief '&&' compound punctuator token code. (double ampersand)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_AMPER_AMPER,      "&&")
/// @brief '||' compound punctuator token code. (double pipe)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_PIPEE_PIPEE,      "||")

/// @brief '<<' compound punctuator token code. (left double arrow)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_LESST_LESST,      "<<")
/// @brief '>>' compound punctuator token code. (right double arrow)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_GREAT_GREAT,      ">>")
/// @brief '==' compound punctuator token code. (double equal)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_EQUAL_EQUAL,      "==")

/// @brief '++' compound punctuator token code. (increment)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_PLUSS_PLUSS,      "++")
/// @brief '--' compound punctuator token code. (decrement)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_MINUS_MINUS,      "--")

/// @brief '..' compound punctuator token code. (double dot)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_POINT_POINT,      "..")
/// @brief '::' compound punctuator token code. (double colon)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_COLON_COLON,      "::")

// Compound punctuators -- Equal

/// @brief '?=' compound punctuator token code. (question equal)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_QUEST_EQUAL,      "?=")
/// @brief '!=' compound punctuator token code. (exclamation equal)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_EXCLM_EQUAL,      "!=")
/// @brief '&=' compound punctuator token code. (ampersand equal)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_AMPER_EQUAL,      "&=")
/// @brief '|=' compound punctuator token code. (pipe equal)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_PIPEE_EQUAL,      "|=")
/// @brief '^=' compound punctuator token code. (caret equal)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_CARET_EQUAL,      "^=")

/// @brief '<=' compound punctuator token code. (less equal)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_LESST_EQUAL,      "<=")
/// @brief '>=' compound punctuator token code. (greater equal)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_GREAT_EQUAL,      ">=")

/// @brief '+=' compound punctuator token code. (plus equal)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_PLUSS_EQUAL,      "+=")
/// @brief '-=' compound punctuator token code. (minus equal)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_MINUS_EQUAL,      "-=")
/// @brief '*=' compound punctuator token code. (asterisk equal)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_STARR_EQUAL,      "*=")
/// @brief '/=' compound punctuator token code. (slash equal)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_SLASH_EQUAL,      "/=")
/// @brief '%=' compound punctuator token code. (percent equal)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_PERCN_EQUAL,      "%=")

/// @brief ':=' compound punctuator token code. (colon equal)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_COLON_EQUAL,      ":=")

// Compound punctuators -- Other

/// @brief '?.' compound punctuator token code. (optional dot)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_QUEST_POINT,      "?.")

/// @brief '<>' compound punctuator token code. (logical biconditional)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_LESST_GREAT,      "<>")
/// @brief '=>' compound punctuator token code. (big arrow)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_ARROW_LARGE,      "=>")
/// @brief '->' compound punctuator token code. (right arrow)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_ARROW_RIGHT,      "->")
/// @brief '<-' compound punctuator token code. (left arrow)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_ARROW_LEFTT,      "<-")

/// @brief '#!' compound punctuator token code. (hashbang)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_SHARP_EXCLM,      "#!")

/// @brief '...' compound punctuator token code. (ellipsis)
calcDefinePunctorToken(CALC_TOKEN_PUNCTOR_ELLIP,            "...")

#ifdef calcDefinePunctorToken
#   undef calcDefinePunctorToken
#endif // UNDEF calcDefinePunctorToken

/* =------------------------------------------------------------= */
