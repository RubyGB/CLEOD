//
// Created by jonwi on 10/14/2019.
//

#include "Compiler.h"

Compiler::Compiler(std::vector<Token> tokens) : tokens(tokens) {
    current = tokens.begin();
}
Bytecode Compiler::compile() const {
    //  do some stuff...
    return Bytecode(code);
}

void Compiler::expression() {

}

void Compiler::grouping() {
    expression();
    //consume(TokenType::RIGHT_PAREN, "Expect \")\" after expression.");
}