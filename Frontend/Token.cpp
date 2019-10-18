//
// Created by jonwi on 10/7/2019.
//

#include <iostream>

#include "Token.h"
#include "../MiddleEnd/Bytecode.h"

std::ostream &operator <<(std::ostream &output, const Token &token) {
    output  << "TOKEN | TYPE [" << std::to_string(static_cast<byte>(token.type))
            << "] | LEXEME [" << token.data << "] | LINE [" << token.line << "]";
    return output;
}