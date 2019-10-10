#include <iostream>

#include "MiddleEnd/Chunk.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::vector<byte> bytes;
    writeInt(bytes, 75);
    writeInt(bytes, 601);
    std::cout << "75 as clint is: " << readInt(bytes, 0) << std::endl; // should output 75
    std::cout << "Should be garbage: " << readInt(bytes, 1) << std::endl; // should read a weird value!
    std::cout << "601 as clint is: " << readInt(bytes, 8) << std::endl; // should output 601

    std::cout << "Writing -75 as clint..." << std::endl;
    writeInt(bytes, -75);
    std::cout << "-75 as clint is: " << readInt(bytes, 16) << std::endl;
    std::cout << "-75 as cluint is: " << readUint(bytes, 16) << std::endl;

    std::cout << "Writing -10000 as cluint..." << std::endl;
    writeUint(bytes, -10000);
    std::cout << "-10000 as cluint: " << readUint(bytes, 24) << std::endl;
    std::cout << "-10000 as clint: " << readInt(bytes, 24) << std::endl;

    return 0;
}