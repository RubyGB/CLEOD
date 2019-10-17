//
// Created by jonwi on 10/14/2019.
//

#ifndef CLEOD_COMPILER_H
#define CLEOD_COMPILER_H

#include "../Frontend/Token.h"
#include "Bytecode.h"

class CompilationException {
private:

public:
    std::string what() const;
};

enum class Precedence {
    PREC_NONE = 0,
    PREC_ASSIGNMENT,    // =
    PREC_OR,            // or
    PREC_AND,           // and
    PREC_EQUALITY,      // == !=
    PREC_COMPARISON,    // < > <= >=
    PREC_TERM,          // + -
    PREC_FACTOR,        // * /
    PREC_UNARY,         // ! -
    PREC_CALL,          // . () []
    PREC_PRIMARY
};

class Compiler;
typedef void (Compiler::*ParseRule)(); // ParseRule is a void function with no arguments, member of Compiler
struct PrattRule {
    ParseRule prefix;
    ParseRule infix;
    Precedence prec;
};
typedef std::unordered_map<TokenType, PrattRule> PrattTable;

class Compiler {
private:
    std::vector<Token> tokens;
    ByteStream code;

    void expression();
    void grouping();
    void unary();
    void binary();
    void integer();
    void floating();

    /*
     * The almighty beast that resides at the heart of our compiler
     */
    const PrattTable CLEOD_PRATT_TABLE = {
            {TokenType::LEFT_PAREN,     {&Compiler::grouping, nullptr, Precedence::PREC_NONE}},
            {TokenType::RIGHT_PAREN,    {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::LEFT_BRACE,     {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::RIGHT_BRACE,    {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::COMMA,          {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::DOT,            {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::MINUS,          {&Compiler::unary, &Compiler::binary, Precedence::PREC_TERM}},
            {TokenType::PLUS,           {nullptr, &Compiler::binary, Precedence::PREC_TERM}},
            {TokenType::SEMICOLON,      {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::SLASH,          {nullptr, &Compiler::binary, Precedence::PREC_FACTOR}},
            {TokenType::STAR,           {nullptr, &Compiler::binary, Precedence::PREC_FACTOR}},
            {TokenType::BANG,           {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::BANG_EQUAL,     {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::EQUAL_EQUAL,    {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::EQUAL,          {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::GREATER,        {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::GREATER_EQUAL,  {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::LESS,           {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::LESS_EQUAL,     {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::LIT_IDENTIFIER, {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::LIT_INTEGER,    {&Compiler::integer, nullptr, Precedence::PREC_NONE}},
            {TokenType::LIT_FLOATING,   {&Compiler::floating, nullptr, Precedence::PREC_NONE}},
            {TokenType::LIT_STRING,     {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::AND,            {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::OR,             {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::IF,             {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::ELSE,           {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::FOR,            {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::WHILE,          {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::SWITCH,         {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::CASE,           {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::TRUE,           {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::FALSE,          {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::AND,            {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::AND,            {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::AND,            {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::RETURN,         {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::VAR,            {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::VOID,           {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::BOOL,           {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::BYTE,           {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::INT,            {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::UINT,           {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::FLOAT,          {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::STRING,         {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::PRINT,          {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::EF,             {nullptr, nullptr, Precedence::PREC_NONE}},
    };
public:
    Compiler(std::vector<Token> tokens);
    //  May throw CompilationException.
    Bytecode compile() const;
};


#endif //CLEOD_COMPILER_H
