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
    //  scan() should fill this up and return a copy of it.
    std::vector<Token> tokens;

    //  Constructor should initialize this.
    std::ifstream src;
public:
    Scanner(const std::string &sourceFileName);
    std::vector<Token> scan();
};


#endif //CLEOD_SCANNER_H
