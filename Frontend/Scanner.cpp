//
// Created by jonwi on 10/7/2019.
//

#include "Scanner.h"

std::vector<Token> Scanner::scanTokens() {
    while(!isAtEnd()){
        start = current;
        scanToken();
    }
    tokens.push_back({TokenType::EF,  "", line});
    return tokens;
}
Scanner::Scanner(const std::string &sourceFileName) {
    source = sourceFileName;
}

// Helper functions for scanTokens()
bool Scanner::isAtEnd() {
    return current >= source.length();
}

void Scanner::scanToken() {

}