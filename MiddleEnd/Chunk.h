//
// Created by jonwi on 10/9/2019.
//

#ifndef CLEOD_CHUNK_H
#define CLEOD_CHUNK_H

#include <cstdint>
#include <vector>

// We will use this typedef all over the place
typedef uint8_t byte;

enum class Opcode : byte {
    OP_PRINT
};

// Bytes will be laid out sequentially in memory, this is the format we will convert them to for execution
// Note that we use a fixed number of potential operands -- this is because a byte pointer takes up 8 bytes of memory,
// so it's way more memory-efficient (potentially 2x smaller files) to store directly the number of operands we need

// Also note that this is easily extendable -- if we need another operand for some esoteric opcode, we can just add one.
struct Operation {
    Opcode op;
    byte operand1;
    byte operand2;
    byte operand3;
};

class Chunk {

};


#endif //CLEOD_CHUNK_H
