//
// Created by jonwi on 10/7/2019.
//

#ifndef CLEOD_SCANNER_H
#define CLEOD_SCANNER_H


#include <fstream>
#include <sstream>


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
    std::unordered_map<std::string, TokenType> keywords = { // mapping keywords to TokenType
            {"true", TokenType::TRUE},
            {"false", TokenType::FALSE},
            {"print", TokenType::PRINT},
            {"if", TokenType::IF},
            {"else", TokenType::ELSE},
            {"for", TokenType::FOR},
            {"return", TokenType::RETURN},
            {"while", TokenType::WHILE},
            {"switch", TokenType::SWITCH},
            {"case", TokenType::CASE}
    };

    // Helper functions:
    bool isAtEnd();
    void scanToken(); // maps character to appropriate TokenType
    char advance(); // advancing character by character
    void addToken(TokenType type); // adds token to token vector
    bool match(char ch); // checks if next character is ch
    char peek();
    char peekNext();
    void stringFunc(); // recognizing string literal
    void numberFunc(); // recognizing number literal
    void identifier(); // recognizing identifier

public:
    // Constructor for Scanner class
    explicit Scanner(const std::string &sourceFileName);
    std::vector<Token> scanTokens();

};


#endif //CLEOD_SCANNER_H
