//
// Created by jonwi on 10/7/2019.
//

#ifndef CLEOD_TOKEN_H
#define CLEOD_TOKEN_H

#include <string>
#include <vector>

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

    EF // end of file. (would have used EOF but C++ insists on reserving it for a macro)
};

struct Token {
    TokenType type;
    //  data is just the string literal. for an identifier token this might be "variableName", for a double literal
    //      it might be "-2.5", etc. this string will be parsed when necessary while compiling to bytecode.
    std::string data;
};


#endif //CLEOD_TOKEN_H
