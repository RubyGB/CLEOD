//
// Created by jonwi on 10/14/2019.
//

#include "Compiler.h"

Compiler::Compiler(std::vector<Token> tokens) : tokens(tokens) {
    current = tokens.begin();
}
Bytecode Compiler::compile() {
    //  do some stuff...
    advance();
    expression();
    if(errors.size() > 0)
        throw CompilationException();
    return Bytecode(code);
}

void Compiler::advance() {
    previous = current;

    while(true) {
        ++current;
        if(current->type != TokenType::ERR) break;

        // TODO: want much better error reporting here.
        addErrorAt(*current, "Error token found in advance() call.");
    }
}

bool Compiler::consume(TokenType match) {
    if(current->type == match) {
        advance();
        return true;
    }
    return false;
}

void Compiler::addErrorAt(const Token &where, std::string what) {
    std::string err = "[line UUNIMPLEMENTED] Error";
    if(where.type == TokenType::EF)
        err += " at end";
    else if(where.type == TokenType::ERR)
        ; // nothing
    else
        err += " at token: " + std::to_string(static_cast<byte>(where.type)) + " where data is: " + where.data;

    err += "\n"
}

void Compiler::expression() {

}

void Compiler::grouping() {
    expression();
    consume(TokenType::RIGHT_PAREN, "Expect \")\" after expression.");
}