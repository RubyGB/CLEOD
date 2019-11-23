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
bool Compiler::checkNext(TokenType type) {
    auto peek = current + 1;
    if(peek->type != type) return false;
    return true;
}

void Compiler::declaration() {
    //  We'll come back to this later and add variables
    if(checkNext(TokenType::COLON_EQUAL)) {
        varDeclaration();
    }
    else if(checkNext(TokenType::EQUAL)) {
        reassignStatement();
    }
    else {
        statement();
    }
}
void Compiler::statement() {
    if(match(TokenType::PRINT)) {
        printStatement();
    }
    if(match(TokenType::IF)) {
        ifStatement();
    }
    if(match(TokenType::WHILE)){
        whileStatement();
    }
}

void Compiler::varDeclaration() {
    //  current + 1 is guaranteed to be TokenType::COLON_EQUAL
    std::string variableID = current->data;
    advance();  //  past LIT_IDENTIFIER
    advance();  //  past :=
    expression();
    consume(TokenType::SEMICOLON, "Expect ';' after variable declaration.");
    code.writeOpcode(Opcode::ASSN);
    code.writeString(variableID);
}
void Compiler::reassignStatement() {
    //  current + 1 is guaranteed to be TokenType::EQUAL
    std::string variableID = current->data;
    advance();  //  past LIT_IDENTIFIER
    advance();  //  past =
    expression();   // parse with precedence PREC_ASSIGNMENT
    consume(TokenType::SEMICOLON, "Expect ';' after variable reassignment.");
    code.writeOpcode(Opcode::REASSN);
    code.writeString(variableID);
}

void Compiler::printStatement() {
    expression();
    consume(TokenType::SEMICOLON, "Expect ';' after value.");
    code.writeOpcode(Opcode::PRINT);
}
void Compiler::ifStatement() {
    consume(TokenType::LEFT_PAREN, "Expect \"(\" after if.");
    grouping();
    code.writeOpcode(Opcode::BNE);
    closureStack.push(code.size()); // store current pc for rewriting
    code.writeUint(-1); //  temporary value

    consume(TokenType::LEFT_BRACE, "Expect \"{\" to scope if statement block.");
    while(current->type != TokenType::RIGHT_BRACE) {
        declaration();
    }
    consume(TokenType::RIGHT_BRACE, "Expect closing \"}\" for if statement.");
    if (current->type == TokenType::ELSE) elseStatement();
    else {
        code.rewriteUint(code.size(), closureStack.top()); // set jump offset
        closureStack.pop();
    }
}

void Compiler::elseStatement(){
    advance();
    code.writeOpcode(Opcode::JMP);

    uint ifpc = closureStack.top();
    closureStack.pop();

    // for JMP
    closureStack.push(code.size()); // store current pc for rewriting
    code.writeUint(-1); //  temporary value

    code.rewriteUint(code.size(), ifpc); // set jump offset

    consume(TokenType::LEFT_BRACE, "Expect \"{\" to scope else statement block.");
    while(current->type != TokenType::RIGHT_BRACE) {
        declaration();
    }
    consume(TokenType::RIGHT_BRACE, "Expect closing \"}\" for else statement.");
    code.rewriteUint(code.size(), closureStack.top()); // set jump offset
    closureStack.pop();
}

void Compiler::whileStatement(){
    consume(TokenType::LEFT_PAREN, "Expect \"(\" after if.");
    uint pc = code.size();
    grouping();
    code.writeOpcode(Opcode::BNE);
    closureStack.push(code.size()); // store current pc for rewriting
    code.writeUint(-1); //  temporary value

    consume(TokenType::LEFT_BRACE, "Expect \"{\" to scope if statement block.");
    while(current->type != TokenType::RIGHT_BRACE) {
        declaration();
    }
    code.writeOpcode(Opcode::JMP);
    code.writeUint(pc);
    consume(TokenType::RIGHT_BRACE, "Expect closing \"}\" for if statement.");
    code.rewriteUint(code.size(), closureStack.top()); // set jump offset
    closureStack.pop();
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
        case TokenType::PLUS:       code.writeOpcode(Opcode::ADD); break;
        case TokenType::MINUS:      code.writeOpcode(Opcode::SUBTRACT); break;
        case TokenType::STAR:       code.writeOpcode(Opcode::MULTIPLY); break;
        case TokenType::SLASH:      code.writeOpcode(Opcode::DIVIDE); break;
        case TokenType::LESS:       code.writeOpcode(Opcode::LT); break;
        default:
            return;
    }
}

void Compiler::identifier() {
    code.writeOpcode(Opcode::LITERAL);
    code.writeDataType(DataType::VAR);
    code.writeString(previous->data);
}
void Compiler::number() {
    code.writeOpcode(Opcode::LITERAL);
    code.writeDataType(DataType::DOUBLE);
    code.writeDouble(std::stod(previous->data));
}

void Compiler::cleodBoolean(){
    code.writeOpcode(Opcode::LITERAL);
    code.writeDataType(DataType::BOOL);
    if (previous->type == TokenType::TRUE){
        code.writeBool(true);
    } else{ code.writeBool(false); }
}

void Compiler::string(){
    code.writeOpcode(Opcode::LITERAL);
    code.writeDataType(DataType::STRING);
    std::string withoutQuotes = previous->data.substr(1, previous->data.length() - 2);
    code.writeString(withoutQuotes);
}

void Compiler::array() {
    code.writeOpcode(Opcode::LITERAL);
    code.writeDataType(DataType::ARRAY);

    //  compile all inside literals
    while(true) {
        expression();
        if(match(TokenType::RIGHT_CHEVRON))
            break;
        if(!match(TokenType::COMMA)) {
            addErrorAt(*current, "Expect ',' between array elements.");
        }
    }
    code.writeOpcode(Opcode::ENDARR);
}

PrattRule Compiler::getRule(TokenType type) const {
    return CLEOD_PRATT_TABLE.at(type);
}