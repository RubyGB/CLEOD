#include <iostream>
#include <limits>

#include "MiddleEnd/Bytecode.h"
#include "Frontend/Token.h"
#include "MiddleEnd/Compiler.h"

/*
 * Catch2 - our unit testing framework!
 * If we have CATCH_CONFIG_MAIN defined, then our program runs tests only.
 * Otherwise, it uses our defined main function.
 */
//#define CATCH_CONFIG_MAIN
#ifndef CATCH_CONFIG_MAIN
int main() {
    std::vector<Token> mockTokens = {
            {TokenType::PRINT, "print", 1},
            {TokenType::LIT_INTEGER, "0", 1},
            {TokenType::SEMICOLON, ";", 1},
            {TokenType::PRINT, "print", 2},
            {TokenType::LEFT_PAREN, "(", 2},
            {TokenType::LIT_INTEGER, "2", 2},
            {TokenType::MINUS, "-", 2},
            {TokenType::LIT_INTEGER, "6", 2},
            {TokenType::RIGHT_PAREN, ")", 2},
            {TokenType::SLASH, "/", 2},
            {TokenType::LIT_FLOATING, "2.4", 2},
            {TokenType::SEMICOLON, ";", 2},
            {TokenType::EF, "", 2}
    };

    Compiler c(mockTokens);
    try {
        Bytecode bc = c.compile();
        try {
            while(true) {
                std::cout << std::to_string(bc.nextByte()) << " ";
            }
        }
        catch(ByteOutOfRangeException &e) {
            std::cout << std::endl;
            std::cout << e.what() << std::endl;
        }
    }
    catch(CompilationException &e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
#endif

#ifdef CATCH_CONFIG_MAIN
#include "Libraries/catch.hpp"
TEST_CASE("read/write for ByteStream to all literal types works", "[ByteStream]") {
    //  All tests are starting from a clean ByteStream
    ByteStream bs;

    SECTION("read/write for ints") {
        bs.writeInt(75);
        bs.writeInt(-87654321);
        REQUIRE(bs.readInt(0) == 75);
        REQUIRE(bs.readInt(8) == -87654321);
        bs = ByteStream();
        for(int i = 0; i < 100; i++)
            bs.writeInt(10 * i);
        for(int i = 0; i < 100; i++)
            REQUIRE(bs.readInt(8 * i) == 10 * i);

        bs = ByteStream();
        bs.writeInt(std::numeric_limits<int>::max());
        REQUIRE(bs.readInt(0) == std::numeric_limits<int>::max());
    }
}
#endif