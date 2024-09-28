# Lexical elemets overview

<!--
Copyright (c) 2024 Federico Cristina

This file is part of the calc scripting language project,
under the Apache License v2.0. See LICENSE for license
informations.
-->

In **calc** programming language, lexical elements, are those language elements scanned
and managed by the lexer. In **calc**, lexical elements, are managed as tokens composed
of a token code and a lexeme; the first one contains a numeric representation of the
lexical element, used to distinguish it from others without the necessity to compare each
time the lexeme, that is a textual representation of the element.

## How they're scanned from source stream?

Each element has an unambiguous pattern associated to him, the lexer recognize the
specified pattern (calling a procedure that scans that specified pattern from the source
stream) and associate to him the token code and the scanned sequence of characters.

## How to store tokens in memory?

An option is to allocate each time a buffer containing the textual sequence of characters,
but this option may slow the process with continuous memory allocation and deallocation.

Another option is to allocate a shared buffer and fill it with the scanned sequence each
time, choosing the token code in the same way of the previous option.

The last option is to store a pointer to the beginning of the lexeme and a related integer
representing the length of the lexeme, choosing the token code in the same way of the
previous option.
