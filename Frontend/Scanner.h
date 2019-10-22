//
// Created by jonwi on 10/7/2019.
//

#ifndef CLEOD_SCANNER_H
#define CLEOD_SCANNER_H

#include <string>
#include <fstream>

#include "Token.h"

class Scanner {
private:
    // Private variables
    int start = 0;
    int current = 0;
    uint64_t line = 0;
    char c;
    //  scan() should fill this up and return a copy of it.
    std::string source;
    std::vector<Token> tokens;

    //  Constructor should initialize this.
    std::ifstream src;
    bool isAtEnd();
    void scanToken();
    char advance();
    void addToken(TokenType type);
    void addToken(TokenType type, std::string data);

public:
    // Constructor for Scanner class
    Scanner(const std::string &sourceFileName);
    std::vector<Token> scanTokens();

};


#endif //CLEOD_SCANNER_H
