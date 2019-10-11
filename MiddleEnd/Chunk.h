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

// Error class for when user tries to read data and hits "eof" for the bytecode/literals
class ByteOutOfRangeException {
private:
    uint where;
    uint max;
public:
    ByteOutOfRangeException(uint where, uint max);
    std::string what();
};

//  LiteralByteStream class is a wrapper for std::vector<byte> that has lots of helper functions for managing
//      inserting/extracting of values into byte stream properly.
class LiteralByteStream {
private:
    std::vector<byte> bytes;
    uint head = 0;

    // Unions for conveniently converting between bytes and data types
    union ClintByteMask {
        clint c;
        byte b[8];
    };
    union CluintByteMask {
        cluint c;
        byte b[8];
    };
    union DoubleByteMask {
        double d;
        byte b[8];
    };
public:
    clint readInt();
    void writeInt(clint val);
    cluint readUint();
    void writeUint(cluint val);
    byte readByte();
    void writeByte(byte val);
    double readDouble();
    void writeDouble(double val);
    bool readBool();
    void writeBool(bool val);
    std::string readString();
    void writeString(std::string val);

    // sets the byte counter to 0
    void resetHead();
    // sets the byte counter directly
    void setHead(uint pos);
    // moves the head / byte counter back by amount
    void stepBack(uint amount);
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
