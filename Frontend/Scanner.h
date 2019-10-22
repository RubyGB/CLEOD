//
// Created by jonwi on 10/7/2019.
//

#ifndef CLEOD_SCANNER_H
#define CLEOD_SCANNER_H

#include <string>
#include <fstream>
#include <sstream>

#include "Token.h"

class Scanner {
private:
    // Private variables
    //
    int start = 0;
    int current = 0;
    uint64_t line = 1;
    char c; // character in the source file
    std::string text;
    std::string source; // copy of the source file as string
    std::vector<Token> tokens; // vector of tokens

    //  Constructor should initialize this.
    std::ifstream src;
    std::stringstream buffer;

    // Helper functions:
    bool isAtEnd();
    void scanToken();
    char advance();
    void addToken(TokenType type);

public:
    // Constructor for Scanner class
    explicit Scanner(const std::string &sourceFileName);
    std::vector<Token> scanTokens();

};


#endif //CLEOD_SCANNER_H
