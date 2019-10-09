#include <iostream>

#include "MiddleEnd/Chunk.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::cout << sizeof(Opcode) << std::endl;
    Operation o;
    //o.operands.push_back(3);
    std::cout << sizeof(o) << std::endl;

    return 0;
}