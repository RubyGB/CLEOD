//
// Created by jonwi on 10/7/2019.
//

#ifndef CLEOD_TOKEN_H
#define CLEOD_TOKEN_H

#include <string>
#include <vector>
#include <unordered_map>

enum class TokenType {
    // Single character:
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE, LEFT_BRACKET, RIGHT_BRACKET,
    COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

    // One or more characters:
    BANG, BANG_EQUAL,
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,
    COLON_EQUAL,
    LEFT_CHEVRON, RIGHT_CHEVRON, // <<, >>

    // Literals: (someVariable, "hello world!", -8, 7.231, etc.)
    LIT_IDENTIFIER, LIT_STRING, LIT_NUMBER,

    // Keywords beyond this point!
    // Control flow keywords:
    IF, ELSE, FOR, WHILE, SWITCH, CASE, AND, OR, TRUE, FALSE, RETURN,
    // Typing keywords (VAR -> dynamic) (some of these may now be unused)
    VAR, VOID, BOOL, BYTE, INT, UINT, FLOAT, STRING,
    // Other keywords
    PRINT,
    ERR,
    EF // end of file. (would have used EOF but C++ insists on reserving it for a macro)
};

struct Token {
    TokenType type;
  
    // thought that these 2 might be helpful later on
  	//String lexeme;
  	//int line;
  	//  you'd be correct! see below + the << operator
  
    //  data is just the string literal. for an identifier token this might be "variableName", for a double literal
    //      it might be "-2.5", etc. this string will be parsed when necessary while compiling to bytecode.
    std::string data;
    //  line number. used for error reporting
    uint64_t line;


    friend std::ostream &operator <<(std::ostream &output, const Token &token);
};

//  This map is just a helper for printing enum names from enums. C++ really should have something built in for this...
const std::unordered_map<TokenType, std::string> TOKEN_TYPE_NAMES = {
        {TokenType::LEFT_PAREN, "LEFT_PAREN"}, {TokenType::RIGHT_PAREN, "RIGHT_PAREN"},
        {TokenType::LEFT_BRACE, "LEFT_BRACE"}, {TokenType::RIGHT_BRACE, "RIGHT_BRACE"},
        {TokenType::LEFT_BRACKET, "LEFT_BRACKET"}, {TokenType::RIGHT_BRACKET, "RIGHT_BRACKET"},
        {TokenType::COMMA, "COMMA"}, {TokenType::DOT, "DOT"},
        {TokenType::MINUS, "MINUS"}, {TokenType::PLUS, "PLUS"},
        {TokenType::SEMICOLON, "SEMICOLON"},
        {TokenType::SLASH, "SLASH"}, {TokenType::STAR, "STAR"},

        {TokenType::BANG, "BANG"}, {TokenType::BANG_EQUAL, "BANG_EQUAL"},
        {TokenType::EQUAL, "EQUAL"}, {TokenType::EQUAL_EQUAL, "EQUAL_EQUAL"},
        {TokenType::GREATER, "GREATER"}, {TokenType::GREATER_EQUAL, "GREATER_EQUAL"},
        {TokenType::LESS, "LESS"}, {TokenType::LESS_EQUAL, "LESS_EQUAL"},
        {TokenType::COLON_EQUAL, "COLON_EQUAL"},
        {TokenType::LEFT_CHEVRON, "LEFT_CHEVRON"}, {TokenType::RIGHT_CHEVRON, "RIGHT_CHEVRON"},

        {TokenType::LIT_IDENTIFIER, "LIT_IDENTIFIER"},
        {TokenType::LIT_STRING, "LIT_STRING"},
        {TokenType::LIT_NUMBER, "LIT_NUMBER"},

        {TokenType::IF, "IF"}, {TokenType::ELSE, "ELSE"},
        {TokenType::FOR, "FOR"}, {TokenType::WHILE, "WHILE"},
        {TokenType::SWITCH, "SWITCH"}, {TokenType::CASE, "CASE"},
        {TokenType::AND, "AND"}, {TokenType::OR, "OR"},
        {TokenType::TRUE, "TRUE"}, {TokenType::FALSE, "FALSE"},
        {TokenType::RETURN, "RETURN"},

        {TokenType::VAR, "VAR"}, {TokenType::VOID, "VOID"},
        {TokenType::BOOL, "BOOL"}, {TokenType::BYTE, "BYTE"},
        {TokenType::INT, "INT"}, {TokenType::UINT, "UINT"},
        {TokenType::FLOAT, "FLOAT"}, {TokenType::STRING, "STRING"},

        {TokenType::PRINT, "PRINT"}, {TokenType::ERR, "ERR"}, {TokenType::EF, "EF"}
};

#endif //CLEOD_TOKEN_H
