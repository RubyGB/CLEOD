//
// Created by jonwi on 10/14/2019.
//

#ifndef CLEOD_COMPILER_H
#define CLEOD_COMPILER_H

#include "../Frontend/Token.h"
#include "Bytecode.h"

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

class CompilationException {
private:

public:
    std::string what() const;
};

class Compiler {
private:
    std::vector<Token> tokens;

    byte expression() const;
public:
    Compiler(std::vector<Token> tokens);
    //  May throw CompilationException.
    Bytecode compile() const;
};


#endif //CLEOD_COMPILER_H
