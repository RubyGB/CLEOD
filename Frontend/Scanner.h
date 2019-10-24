//
// Created by jonwi on 10/7/2019.
//

#ifndef CLEOD_SCANNER_H
#define CLEOD_SCANNER_H


#include <fstream>
#include <sstream>
#include <string.h>

#include "Token.h"

class Scanner {
private:
    // Private variables
    int start = 0;
    int current = 0;
    uint64_t line = 1;
    char c; // character in the source file

    std::string text; // the substring that is recognized as token = token data
    std::string source; // copy of the source file as string
    std::vector<Token> tokens; // vector of tokens
    std::ifstream src; //  Constructor should initialize this.
    std::stringstream buffer; // buffer that holds the contents of file

    // Helper functions:
    bool isAtEnd();
    void scanToken(); // maps character to appropriate TokenType
    char advance(); // advancing character by character
    void addToken(TokenType type); // adds token to token vector
    void addToken(TokenType type, void* literal); // overloaded
    bool match(char c); // checks if next character is c
    char peek();
    char peekNext();
    void stringFunc();
    void numberFunc();

public:
    // Constructor for Scanner class
    explicit Scanner(const std::string &sourceFileName);
    std::vector<Token> scanTokens();

};


#endif //CLEOD_SCANNER_H
