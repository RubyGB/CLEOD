//
// Created by jonwi on 10/14/2019.
//

#include <iostream>
#include <sstream>

#include "Compiler.h"

std::ostream& operator<<(std::ostream &output, const CompilationError &error) {
    output << "Compilation error at " << error.t << " : " << error.msg;
    return output;
}

CompilationException::CompilationException(std::vector<CompilationError> errs) : errors(errs) {}
std::string CompilationException::what() const {
    std::string report = std::to_string(errors.size()) + " errors were found:\n";
    std::ostringstream errorstream;
    for(const CompilationError &err : errors)
        errorstream << err << std::endl;
    report += errorstream.str();
    return report;
}

Compiler::Compiler(std::vector<Token> tokens) : tokens(tokens) {
    current = tokens.begin();
    previous = tokens.begin();
}
Bytecode Compiler::compile() {
    //  do some stuff...
    advance();
    expression();
    if(errors.size() > 0)
        throw CompilationException(errors);
    return Bytecode(code);
}

void Compiler::advance() {
    previous = current;

    while(true) {
        ++current;
        if(current->type != TokenType::ERR) break;

        // TODO: want much better error reporting here?
        addErrorAt(*current, "Error token found in advance() call.");
    }
}

void Compiler::consume(TokenType match, std::string onFailMessage) {
    if(current->type == match) {
        advance();
        return;
    }
    addErrorAt(*current, onFailMessage);
}

void Compiler::addErrorAt(const Token &where, std::string what) {
    errors.push_back({where, what});
}

void Compiler::expression() {
    parseWithPrecedence(Precedence::PREC_ASSIGNMENT);
}

void Compiler::grouping() {
    expression();
    consume(TokenType::RIGHT_PAREN, "Expect \")\" after expression.");
}

void Compiler::unary() {
    TokenType operatorType = parser.previous.type;
    // compile the operand
    parseWithPrecedence(Precedence::PREC_UNARY);
    // Emit the operator instruction
    switch (operatorType){
        case TOKEN_MINUS: code.writeOpcode(Opcode::NEGATE);
        break;
        default:
            return;
    }
}
void Compiler::binary() {

}
void Compiler::integer() {
    //  Dunno if this is right but it's the rough idea.
    code.writeOpcode(Opcode::LITERAL);
    code.writeDataType(DataType::INT);
    code.writeInt(std::stoi(previous->data));
}
void Compiler::floating() {
    code.writeOpcode(Opcode::LITERAL);
    code.writeDataType(DataType::DOUBLE);
    code.writeDouble(std::stod(previous->data));
}