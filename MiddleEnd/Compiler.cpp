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
    for (const CompilationError &err : errors)
        errorstream << err << std::endl;
    report += errorstream.str();
    return report;
}

Precedence nextHighest(Precedence prec) {
    int next = static_cast<int>(prec) + 1;
    if(next >= static_cast<int>(Precedence::PREC_PRIMARY))
        return Precedence::PREC_PRIMARY;
    else
        return static_cast<Precedence>(next);
}

Compiler::Compiler(std::vector<Token> tokens) : tokens(tokens) {
    previous = this->tokens.begin();
    current = this->tokens.begin();
}
Bytecode Compiler::compile() {
    //  do some stuff...

    while(!match(TokenType::EF)) {
        declaration();
    }

    if(errors.size() > 0)
        throw CompilationException(errors);
    return Bytecode(code);
}

void Compiler::parseWithPrecedence(Precedence prec) {
    advance();
    ParseRule prefixRule = CLEOD_PRATT_TABLE.at(previous->type).prefix;
    if(prefixRule == nullptr) {
        addErrorAt(*previous, "Expect expression.");
        return;
    }

    (this->*prefixRule)();

    while(prec <= getRule(current->type).prec) {
        advance();
        ParseRule infixRule = getRule(previous->type).infix;

        (this->*infixRule)();
    }
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

bool Compiler::match(TokenType type) {
    if(current->type != type) return false;
    advance();
    return true;
}

void Compiler::declaration() {
    //  We'll come back to this later and add variables
    statement();
}
void Compiler::statement() {
    if(match(TokenType::PRINT)) {
        printStatement();
    }
}

void Compiler::printStatement() {
    expression();
    consume(TokenType::SEMICOLON, "Expect ';' after value.");
    code.writeOpcode(Opcode::PRINT);
}
void Compiler::expressionStatement() {
    // TODO IMPLEMENT
}

void Compiler::expression() {
    parseWithPrecedence(Precedence::PREC_ASSIGNMENT);
}

void Compiler::grouping() {
    expression();
    consume(TokenType::RIGHT_PAREN, "Expect \")\" after expression.");
}

void Compiler::unary() {
    TokenType operatorType = previous->type;
    // compile the operand
    parseWithPrecedence(Precedence::PREC_UNARY);
    // Emit the operator instruction
    switch (operatorType){
        case TokenType::MINUS : code.writeOpcode(Opcode::NEGATE);
            break;
        default:
            return;
    }
}
void Compiler::binary() {
    // Remember the operator
    TokenType operatorType = previous->type;
    // compile right opperand
    parseWithPrecedence(nextHighest(getRule(operatorType).prec));
    switch (operatorType){
        case TokenType::PLUS:    code.writeOpcode(Opcode::ADD); break;
        case TokenType::MINUS:   code.writeOpcode(Opcode::SUBTRACT); break;
        case TokenType::STAR:    code.writeOpcode(Opcode::MULTIPLY); break;
        case TokenType::SLASH:   code.writeOpcode(Opcode::DIVIDE); break;
        default:
            return;
    }
}
void Compiler::number() {
    code.writeOpcode(Opcode::LITERAL);
    code.writeDataType(DataType::DOUBLE);
    code.writeDouble(std::stod(previous->data));
}

PrattRule Compiler::getRule(TokenType type) const {
    return CLEOD_PRATT_TABLE.at(type);
}