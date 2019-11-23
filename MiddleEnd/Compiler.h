//
// Created by jonwi on 10/14/2019.
//

#ifndef CLEOD_COMPILER_H
#define CLEOD_COMPILER_H

#include <stack>
#include "../Frontend/Token.h"
#include "Bytecode.h"

struct CompilationError {
    Token t;
    std::string msg;

    friend std::ostream &operator <<(std::ostream &output, const CompilationError &error);
};

class CompilationException {
private:
    std::vector<CompilationError> errors;
public:
    CompilationException(std::vector<CompilationError> errs);
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

Precedence nextHighest(Precedence prec);

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
    //  Note we bother storing iterators in case the lexer generates error tokens - we "skip" these, i.e.:
    //      If our tokens are LIT_INTEGER | ERR | ERR | LIT_FLOATING,
    //      then previous will point to LIT_INTEGER and current will point to LIT_FLOATING
    std::vector<Token> tokens;
    std::vector<Token>::const_iterator current;
    std::vector<Token>::const_iterator previous;

    //  The entire job of Compiler is to fill this up, and return a Bytecode(code). Many functions will be accessing it.
    ByteStream code;
    std::stack<uint> closureStack;

    //  If we encounter any error tokens or unexpected tokens (e.g. no closing RIGHT_PAREN after a LEFT_PAREN,
    //      then we push them in here through addErrorAt(). If this is nonempty when we finish compiling,
    //      we throw a CompilationException(errors) for the calling code to catch in a try/catch.
    std::vector<CompilationError> errors;

    //  Advances the previous/current Token iterators, skipping any error tokens.
    void advance();

    void parseWithPrecedence(Precedence prec);

    //  Confirms whether the current token is as expected or not, and if so, calls advance(). If not,
    //      makes a call to addErrorAt().
    void consume(TokenType match, std::string onFailMessage);

    //  Add errors to errors vector. If this is nonempty when compile completes we throw a CompilationException.
    void addErrorAt(const Token &where, std::string what);

    bool match(TokenType type);
    bool checkNext(TokenType type);

    void declaration();
    void statement();

    void varDeclaration();
    void reassignStatement();

    void printStatement();
    void expressionStatement();
    void ifStatement();
    void elseStatement();
    void whileStatement();

    void expression();
    void grouping();
    void unary();
    void binary();

    void identifier();
    void number();
    void cleodBoolean(); // compliation of boolean - had to name it cleodBoolean, boolean defined in fragment.cpp
    void string();
    void array();
    PrattRule getRule(TokenType type) const;
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
            {TokenType::LESS,           {nullptr, &Compiler::binary, Precedence::PREC_COMPARISON}},
            {TokenType::LESS_EQUAL,     {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::COLON_EQUAL,    {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::LEFT_CHEVRON,   {&Compiler::array, nullptr, Precedence::PREC_NONE}},
            {TokenType::RIGHT_CHEVRON,  {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::LIT_IDENTIFIER, {&Compiler::identifier, nullptr, Precedence::PREC_NONE}},
            {TokenType::LIT_NUMBER,     {&Compiler::number, nullptr, Precedence::PREC_NONE}},
            {TokenType::LIT_STRING,     {&Compiler::string, nullptr, Precedence::PREC_NONE}},
            {TokenType::AND,            {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::OR,             {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::IF,             {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::ELSE,           {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::FOR,            {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::WHILE,          {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::SWITCH,         {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::CASE,           {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::TRUE,           {&Compiler::cleodBoolean, nullptr, Precedence::PREC_NONE}},
            {TokenType::FALSE,          {&Compiler::cleodBoolean, nullptr, Precedence::PREC_NONE}},
            {TokenType::AND,            {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::AND,            {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::AND,            {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::RETURN,         {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::VAR,            {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::VOID,           {nullptr, nullptr, Precedence::PREC_NONE}},
            {TokenType::BOOL,           {&Compiler::cleodBoolean, nullptr, Precedence::PREC_NONE}},
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

    //  May throw CompilationException when called. Make sure to try/catch!
    Bytecode compile();
};


#endif //CLEOD_COMPILER_H
