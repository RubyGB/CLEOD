//
// Created by jonwi on 10/7/2019.
//

#ifndef CLEOD_TOKEN_H
#define CLEOD_TOKEN_H

enum class TokenType {
    // Single character:
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

    // One or more characters:
    BANG, BAND_EQUAL,
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,

    // Literals: (someVariable, "hello world!", -8, 7.231, etc.)
    LIT_IDENTIFIER, LIT_STRING, LIT_INTEGER, LIT_FLOATING,

    // Keywords beyond this point!
    // Control flow keywords:
    IF, ELSE, FOR, WHILE, SWITCH, CASE, AND, OR, TRUE, FALSE, RETURN,
    // Typing keywords (VAR -> dynamic)
    VAR, VOID, BOOL, BYTE, INT, UINT, FLOAT, STRING,
    // Other keywords
    PRINT,

    EOF
};

class Token {

};


#endif //CLEOD_TOKEN_H
