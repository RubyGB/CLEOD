#include <iostream>

#include "MiddleEnd/Bytecode.h"
#include "Frontend/Token.h"
#include "MiddleEnd/Compiler.h"

/*
 * Catch2 - our unit testing framework!
 * If we have CATCH_CONFIG_MAIN defined, then our program runs tests only.
 * Otherwise, it uses our defined main function.
 */
#define CATCH_CONFIG_MAIN
#include "Libraries/catch.hpp"
#ifndef CATCH_CONFIG_MAIN
int main() {
    std::cout << "Testing Token << operator..." << std::endl;
    Token testToken = {TokenType::LIT_INTEGER, "540", 0};
    std::cout << testToken << std::endl;

    std::cout << "Testing CompilationError << operator..." << std::endl;
    CompilationError testCompError = {testToken, "Something bad happened!"};
    std::cout << testCompError << std::endl;

    std::cout << "Testing CompilationException what() function..." << std::endl;
    Token testTokenTwo = {TokenType::GREATER, ">", 0};
    CompilationException compExceptionTest({{testToken, "One bad thing happened!"},{testTokenTwo, "Another bad thing happened!"}});
    std::cout << compExceptionTest.what();

    std::cout << "Testing bytecode class..." << std::endl;
    ByteStream code;
    code.writeOpcode(Opcode::LITERAL);
    code.writeDataType(DataType::INT);
    code.writeInt(7401586);
    code.writeOpcode(Opcode::PRINT);
    Bytecode bc(code);
    //  here VirtualMachine would push Data with the int converted to bytes via Data.data.writeInt(7401586)
    //  Then PRINT would consume the top value on the stack, check its DataType and print it out.
    return 0;
}
#endif

TEST_CASE("read/write for ByteStream to all literal types works", "[ByteStream]") {
    //  All tests are starting from a clean ByteStream
    ByteStream bs;
    SECTION("read/write for ints") {
        bs.writeInt(75);
        REQUIRE(bs.readInt(0) == 75);
    }
}