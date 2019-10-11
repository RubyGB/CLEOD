#include <iostream>

#include "MiddleEnd/Chunk.h"

int main() {
    //  Note that in practice we wouldn't be doing all this stepping back -- the usual data flow would be writing all
    //      the bytecode into a file, then reading it in sequence to execute it in the virtual machine.
    //      reset() and stepBack() are moreso utility/debugging functions.

    std::cout << "Basic tests on writing/reading data..." << std::endl;
    LiteralByteStream lbs;
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

    std::cout << "Size of Operation: " << sizeof(Operation) << std::endl;
    return 0;
}