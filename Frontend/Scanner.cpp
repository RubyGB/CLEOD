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
    tokens.push_back({TokenType::EF,  "", line});
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
        case '<':
            if (match('=')){addToken(TokenType::LESS_EQUAL);}
            else {addToken(TokenType::LESS);}
        case '>':
            if (match('=')){addToken(TokenType::GREATER_EQUAL);}
            else {addToken(TokenType::GREATER);}
    }
}

// Helper functions for scanToken()
char Scanner::advance() {
    current++;
    return source.at(current - 1);
}

void Scanner::addToken(TokenType type) {
    text = source.substr(start, current-start);
    tokens.push_back({type, text, line});
}

