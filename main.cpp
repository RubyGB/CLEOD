#include <iostream>

#include "MiddleEnd/Bytecode.h"
#include "Frontend/Token.h"
#include "MiddleEnd/Compiler.h"

int main() {
    std::cout << "Basic tests on writing/reading literal data..." << std::endl;
    ByteStream lbs;
    lbs.writeInt(75);
    lbs.writeInt(601);
    std::cout << "75 as clint is: " << lbs.readInt(0) << std::endl; // should output 75
    std::cout << "Should be garbage: " << lbs.readInt(7) << std::endl; // should read a weird value!
    std::cout << "601 as clint is: " << lbs.readInt(8) << std::endl; // should output 601

    std::cout << "Writing -75 as clint..." << std::endl;
    lbs.writeInt(-75);
    std::cout << "-75 as clint is: " << lbs.readInt(16) << std::endl;
    std::cout << "-75 as cluint is: " << lbs.readUint(16) << std::endl;

    std::cout << "Writing -10000 as cluint..." << std::endl;
    lbs.writeUint(-10000);
    std::cout << "-10000 as cluint: " << lbs.readUint(24) << std::endl;
    std::cout << "-10000 as clint: " << lbs.readInt(24) << std::endl;

    std::cout << "Writing 240 as byte..." << std::endl;
    lbs.writeByte(240);
    std::cout << "240 as byte: " << std::to_string(lbs.readByte(32)) << std::endl;

    std::cout << "Writing 3.1415 as double..." << std::endl;
    lbs.writeDouble(3.1415);
    std::cout << "3.1415 as double: " << lbs.readDouble(33) << std::endl;

    std::cout << "Writing true then false as bool..." << std::endl;
    lbs.writeBool(true);
    lbs.writeBool(false);
    std::cout << "True as bool is: " << std::to_string(lbs.readBool(41)) << std::endl;
    std::cout << "False as bool is: " << std::to_string(lbs.readBool(42)) << std::endl;

    std::cout << "Writing \"Hello, World!\" as string..." << std::endl;
    lbs.writeString("Hello, World!");
    std::cout << "Resulting string after retrieval from bytecode: " << lbs.readString(43) << std::endl;

    std::cout << "Now let's see what readString() does from the beginning of the bytecode stream..." << std::endl;
    std::cout << "Result: " << lbs.readString(0) << std::endl;
    std::cout << "Unsurprising behaviour, since most bytes in a clint are empty -> null character." << std::endl;

    std::cout << "Testing << and [] operators for ByteStream..." << std::endl;
    ByteStream optestStream;
    optestStream << 240;
    std::cout << "240 is: " << std::to_string(optestStream[0]) << std::endl;

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