#include <iostream>

#include "MiddleEnd/Chunk.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::vector<byte> bytes;
    writeInt(bytes, 75);
    writeInt(bytes, 601);
    std::cout << readInt(bytes, 0) << std::endl; // should output 75
    std::cout << readInt(bytes, 1) << std::endl; // should read a weird value!
    std::cout << readInt(bytes, 8) << std::endl; // should output 601
    return 0;
}