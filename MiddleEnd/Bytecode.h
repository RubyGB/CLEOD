//
// Created by jonwi on 10/9/2019.
//

#ifndef CLEOD_BYTECODE_H
#define CLEOD_BYTECODE_H

#include <cstdint>
#include <vector>
#include <unordered_map>
#include <limits>

// We will use these typedefs all over the place
typedef uint8_t byte;
typedef uint32_t uint;

typedef int64_t clint;
typedef uint64_t cluint;
// Require double to be in IEC60559 format -- note that this also forces it to be 64 bits.
static_assert(std::numeric_limits<double>::is_iec559, "CLEOD requires double to be in IEC60559 format to compile.");

//  Prefix operators compile their arguments first, then themselves (i.e.: print 0 becomes LITERAL 0 PRINT)
//  Infix operators compile their second argument first, taking advantage of the fact that their first argument was
//      compiled as a prefix operator. For example:
//      2 + 3; becomes LITERAL 2 ( + 3) becomes LITERAL 2 LITERAL 3 ADD
enum class Opcode : byte {
    //  prefix operators:
    LITERAL,
    PRINT,
    NEGATE,
    //  infix operators:
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,

    //  For statements:
    POP,
};

enum class DataType : byte {
    INT = 0, UINT, BYTE, DOUBLE, BOOL, STRING, OPCODE, VAR
};

// Error class for when user tries to read data and hits eof for the bytestream/bytecode
class ByteOutOfRangeException {
private:
    uint where;
    uint max;
public:
    ByteOutOfRangeException(uint where, uint max);
    std::string what() const;
};

//  ByteStream class is a wrapper for std::vector<byte> that has lots of helper functions for managing
//      inserting/extracting of values into byte stream properly.
class ByteStream {
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
    Opcode readOpcode(uint pos) const;
    void writeOpcode(Opcode val);
    DataType readDataType(uint pos) const;
    void writeDataType(DataType val);

    byte operator [](uint i) const;
    byte &operator [](uint i);
    void operator <<(byte b);
    uint size() const;
};

//  Class containing byte streams and functionality to read and progress through bytecode properly
class Bytecode {
private:
    ByteStream code;
    //  program counter
    uint pc = 0;
public:
    Bytecode(ByteStream code);

    Opcode nextOpcode();
    clint nextInt();
    cluint nextUint();
    byte nextByte();
    double nextDouble();
    bool nextBool();
    std::string nextString();

    void resetHead();
    void setHead(uint pos);
    void stepBack(uint amount);
    void stepForward(uint amount);
};

#endif //CLEOD_BYTECODE_H
