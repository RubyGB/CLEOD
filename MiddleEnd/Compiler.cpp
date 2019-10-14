//
// Created by jonwi on 10/14/2019.
//

#include "Compiler.h"

Compiler::Compiler(std::vector<Token> tokens) : tokens(tokens) {}
Bytecode Compiler::compile() const {
    ByteStream code;
    //  do some stuff...
    return Bytecode(code);
}