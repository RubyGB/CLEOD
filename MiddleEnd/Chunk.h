//
// Created by jonwi on 10/9/2019.
//

#ifndef CLEOD_CHUNK_H
#define CLEOD_CHUNK_H

#include <cstdint>
#include <vector>
#include <unordered_map>
#include <limits>

// We will use these typedefs all over the place
typedef uint8_t byte;
typedef unsigned int uint;

typedef int64_t clint;
typedef uint64_t cluint;
// Require double to be in IEC60559 format -- note that this also forces it to be 64 bits.
static_assert(std::numeric_limits<double>::is_iec559, "CLEOD requires double to be in IEC60559 format to compile.");

//  Declarations for helper functions to convert a set of bytes into the appropriate type and vice versa
//  note that we pass a reference to a byte vector and a position. this allows us to do range checking and report errors
//      when the literal ends up out of bounds.
clint readInt(const std::vector<byte> &bytes, uint pos);
void writeInt(std::vector<byte> &bytes, clint val);
cluint readUint(const std::vector<byte> &bytes, uint pos);
void writeUint(std::vector<byte> &bytes, cluint val);
double readDouble(const std::vector<byte> &bytes, uint pos);
bool readBool(const std::vector<byte> &bytes, uint pos);
std::string readString(const std::vector<byte> &bytes, uint pos);


enum class Opcode : byte {
    OP_PRINT // 1-operand. Specifies index of literal to print.
};

// Bytes will be laid out sequentially in memory, this is the format we will convert them to for execution
// Note that we use a fixed number of potential operands -- this is because a byte pointer takes up 8 bytes of memory,
// so it's way more memory-efficient (potentially 2x smaller files) to store directly the max number of operands we need

// Also note that this is easily extendable -- if we need another operand for some esoteric opcode, we can just add one.
struct Operation {
    Opcode op;
    byte operand1;
    byte operand2;
    byte operand3;
};

// Due to overhead, Chunk is size 52 -- we can fit lots of bytecode in a single chunk, though! We're really only limited
// by the max number of constants
class Chunk {
    std::vector<Operation> bytecode;

    // indexMap takes a literal index and gives you the actual index in the literals vector
    // note that strings are NULL-TERMINATED in the literals vector - they are variable length and we only give the
    // starting position!
    std::vector<byte> literals; // will have to use helper methods to convert byte stream into corresponding value
    std::unordered_map<byte, uint> indexMap;
};


#endif //CLEOD_CHUNK_H
