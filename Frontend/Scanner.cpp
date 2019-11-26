//
// Created by jonwi on 10/7/2019.
//

#include "Scanner.h"

Scanner::Scanner(const std::string &sourceFileName) {
    c = '0';
    src = std::ifstream(sourceFileName);
    buffer << src.rdbuf();
    source = buffer.str(); // store file content as a string
}

std::vector<Token> Scanner::scanTokens() {
    while(!isAtEnd()){
        start = current;
        scanToken();
    }
    tokens.push_back({TokenType::EF, "", line});
    return tokens;
}

// Helper functions for scanTokens()
bool Scanner::isAtEnd() {
    return current >= source.length();
}

void Scanner::scanToken() {
    c = advance();
    switch(c){
        case '(': addToken(TokenType::LEFT_PAREN); break;
        case ')': addToken(TokenType::RIGHT_PAREN); break;
        case '{': addToken(TokenType::LEFT_BRACE); break;
        case '}': addToken(TokenType::RIGHT_BRACE); break;
        case '[': addToken(TokenType::LEFT_BRACKET); break;
        case ']': addToken(TokenType::RIGHT_BRACKET); break;
        case ',': addToken(TokenType::COMMA); break;
        case '.': addToken(TokenType::DOT); break;
        case '-': addToken(TokenType::MINUS); break;
        case '+': addToken(TokenType::PLUS); break;
        case ';': addToken(TokenType::SEMICOLON); break;
        case '/': addToken(TokenType::SLASH); break;
        case '*': addToken(TokenType::STAR); break;
        case '\n': line++; break;
        // match cases
        case '!':
            if (match('=')) {addToken(TokenType::BANG_EQUAL);}
            else {addToken(TokenType::BANG);}
            break;
        case '=':
            if (match('=')){addToken(TokenType::EQUAL_EQUAL);}
            else {addToken(TokenType::EQUAL);}
            break;
        case '<':
            if (match('=')){addToken(TokenType::LESS_EQUAL);}
            else if(match('<')){addToken(TokenType::LEFT_CHEVRON);}
            else {addToken(TokenType::LESS);}
            break;
        case '>':
            if (match('=')){addToken(TokenType::GREATER_EQUAL);}
            else if(match('>')){addToken(TokenType::RIGHT_CHEVRON);}
            else {addToken(TokenType::GREATER);}
            break;
        case ':':
            if(match('=')){addToken(TokenType::COLON_EQUAL);}
            break;
        // comment case - long lexemes
        case '#':
            while (peek() != '\n' && !isAtEnd()){advance();} break;

        // '', /r /t
        case ' ':
        case '\r':
        case '\t':
            break;
        // string literals
        case '"': stringFunc(); break;
        default:
            if (isdigit(c)){
                numberFunc();
            }
            else if (isalpha(c)){
                identifier();
            }else{
                //throw error
            }
    }
}

// Helper functions for scanToken()
char Scanner::advance() {
    current++;
    return source.at(current - 1);
}

// when adding strings might have issue where quotes are added,
// could this be resolved with compiler?
void Scanner::addToken(TokenType type) {
    text = source.substr(start, current-start);
    tokens.push_back({type, text, line});
}

bool Scanner::match(char ch){
    if (isAtEnd()) {return false;}
    if (source.at(current) != ch) {return false;} // charAt() is at() -> correct?
    ++current;
    return true;
}

char Scanner::peek(){
    if (isAtEnd()) return '\0';
    return source.at(current);
}

char Scanner::peekNext(){
    if (current + 1 >= source.length()){return '\0';} // null terminate
    return source.at(current + 1);
}

void Scanner::stringFunc(){
    while (peek() != '"' && !isAtEnd()){
        if (peek() == '\n'){line++;}
        advance();
    }
    if (isAtEnd()){
        // need to throw error here
        return;
    }
    // this is needed for closing "
    advance();
    addToken(TokenType::LIT_STRING);
}

void Scanner::numberFunc(){
    while(isdigit(peek())){ advance();}
    if (peek() == '.' && isdigit(peekNext())){
        // to consume "."
        advance();
        while (isdigit(peek())) advance();
    }
    addToken(TokenType::LIT_NUMBER);
}

void Scanner::identifier(){
    while (isalnum(peek())) {advance();} // first val must be num (solved in switch case, through isalpha function)
    // checking for keywords
    std::string txt = source.substr(start, current - start);
    auto reserved = keywords.find(txt);
    if(reserved != keywords.end()) {
        addToken(reserved->second);
    }
    else {
        addToken(TokenType::LIT_IDENTIFIER);
    }
}

