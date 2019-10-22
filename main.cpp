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
#define CATCH_CONFIG_MAIN
#ifndef CATCH_CONFIG_MAIN
int main() {
    return 0;
}
#endif

#ifdef CATCH_CONFIG_MAIN
#include "Libraries/catch.hpp"
#include "Frontend/Scanner.h"

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

TEST_CASE("testing scanner class for single tokens", "[Scanner]"){
    Scanner spanner("Cleod1.cleod");
    std::vector<Token> bector = spanner.scanTokens();
    for(int i=0; i<bector.size(); i++)
        std::cout << bector.at(i) << ' ';
}
#endif