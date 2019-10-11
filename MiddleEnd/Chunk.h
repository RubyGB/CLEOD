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

// Error class for when user tries to read data and hits "eof" for the bytecode/literals
class ByteOutOfRangeException {
private:
    uint where;
    uint max;
public:
    ByteOutOfRangeException(uint where, uint max);
    std::string what() const;
};

//  LiteralByteStream class is a wrapper for std::vector<byte> that has lots of helper functions for managing
//      inserting/extracting of literal values into byte stream properly.
class LiteralByteStream {
private:
    std::vector<byte> bytes;

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
    clint readInt(uint pos) const;
    void writeInt(clint val);
    cluint readUint(uint pos) const;
    void writeUint(cluint val);
    byte readByte(uint pos) const;
    void writeByte(byte val);
    double readDouble(uint pos) const;
    void writeDouble(double val);
    bool readBool(uint pos) const;
    void writeBool(bool val);
    std::string readString(uint pos) const;
    void writeString(std::string val);
};

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

class OperationOutOfRangeException {
private:
    uint where;
    uint max;
public:
    OperationOutOfRangeException(uint where, uint max);
    std::string what() const;
};

//  Class for writing/reading operations to a stream of bytes.
class OperationByteStream {
private:
    std::vector<Operation> bytecode;
    uint head = 0;
public:
    const Operation &readOp();
    void writeOp(Operation op);

    void resetHead();
    void setHead(uint pos);
    void stepBack(uint amount);
};

class Chunk {
    OperationByteStream bytecode;
    LiteralByteStream literals;

    // indexMap takes a literal index and gives you the actual index in the literals vector
    // note that strings are NULL-TERMINATED in the literals vector - they are variable length and we only give the
    // starting position!
    std::unordered_map<byte, uint> indexMap;


    //  note: when compiling and writing to indexMap, we will implement literal re-use checking. i.e. if we have the
    //      literal 1 at index 4, and we come across a new literal to compile, then we check if it *already exists* at
    //      any particular index. if so, we just reuse this index. For commonly used literals such as 0, 1 etc. this
    //      can save up to 16 bytes per literal
};


#endif //CLEOD_CHUNK_H
