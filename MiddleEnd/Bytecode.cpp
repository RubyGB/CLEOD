//
// Created by jonwi on 10/9/2019.
// daniel was is
//

#include "Bytecode.h"
#include <iostream>
#include <string>

ByteOutOfRangeException::ByteOutOfRangeException(uint where, uint max) : where(where), max(max) {}
std::string ByteOutOfRangeException::what() const {
    return "Attempted to access byte " + std::to_string(where) + " when maximum byte was " + std::to_string(max) + ".";
}

const uint64_t BYTE_MASK = 0xFF;

clint ByteStream::readInt(uint pos) const {
    ClintByteMask cbm = {0};
    for(uint end = pos + 8; pos < end; pos++) {
        if(pos >= bytes.size())
            throw ByteOutOfRangeException(pos, bytes.size() - 1);
        cbm.b[(8 - end) + pos] = bytes[pos];
    }
    return cbm.c;
}
void ByteStream::writeInt(clint val) {
    for(int j = 0; j < 8; j++) {
        bytes.push_back((val & (BYTE_MASK << 8 * j)) >> 8 * j);
    }
}
cluint ByteStream::readUint(uint pos) const {
    CluintByteMask cbm = {0};
    for(uint end = pos + 8; pos < end; pos++) {
        if(pos >= bytes.size())
            throw ByteOutOfRangeException(pos, bytes.size() - 1);
        cbm.b[(8 - end) + pos] = bytes[pos];
    }
    return cbm.c;
}
void ByteStream::writeUint(cluint val) {
    for(int j = 0; j < 8; j++)
        bytes.push_back((val & (BYTE_MASK << 8 * j)) >> 8 * j);
}
byte ByteStream::readByte(uint pos) const {
    if(pos >= bytes.size())
        throw ByteOutOfRangeException(pos, bytes.size() - 1);
    return bytes[pos];
}
void ByteStream::writeByte(byte val) {
    bytes.push_back(val);
}
double ByteStream::readDouble(uint pos) const {
    DoubleByteMask dbm = {0};
    for(uint end = pos + 8; pos < end; pos++) {
        if(pos >= bytes.size())
            throw ByteOutOfRangeException(pos, bytes.size() - 1);
        dbm.b[(8 - end) + pos] = bytes[pos];
    }
    return dbm.d;
}
void ByteStream::writeDouble(double val) {
    DoubleByteMask dbm = {val};
    for(int j = 0; j < 8; j++)
        bytes.push_back(dbm.b[j]);
}
bool ByteStream::readBool(uint pos) const {
    if(pos >= bytes.size())
        throw ByteOutOfRangeException(pos, bytes.size() - 1);
    if(bytes[pos])
        return true;
    return false;
}
void ByteStream::writeBool(bool val) {
    bytes.push_back(val ? 1 : 0);
}
std::string ByteStream::readString(uint pos) const {
    //  Strings in bytecode are NULL-TERMINATED. So we go until we find a '\0' character or go out of bounds.
    //      Note that this is a really easy way to throw an exception or get spooky behaviour if there's no string at pc.
    //      Also note that since most clints will have plenty of empty bytes, this will probably not throw error in most cases.
    char c;
    std::string result = "";
    if(pos >= bytes.size())
        throw ByteOutOfRangeException(pos, bytes.size() - 1);
    while((c = static_cast<char>(bytes[pos++])) != '\0') {
        if(pos >= bytes.size())
            throw ByteOutOfRangeException(pos, bytes.size() - 1);
        result += c;
    }
    return result;
}
void ByteStream::writeString(std::string val) {
    for(char c : val)
        bytes.push_back(static_cast<byte>(c));
    bytes.push_back(static_cast<byte>('\0'));
}
Opcode ByteStream::readOpcode(uint pos) const {
    return static_cast<Opcode>(readByte(pos));
}
void ByteStream::writeOpcode(Opcode val) {
    writeByte(static_cast<byte>(val));
}
DataType ByteStream::readDataType(uint pos) const {
    return static_cast<DataType>(readByte(pos));
}
void ByteStream::writeDataType(DataType val) {
    writeByte(static_cast<byte>(val));
}

byte ByteStream::operator[](uint i) const {
    if(i >= bytes.size())
        throw ByteOutOfRangeException(i, bytes.size() - 1);
    return bytes[i];
}
byte &ByteStream::operator[](uint i) {
    if(i >= bytes.size())
        throw ByteOutOfRangeException(i, bytes.size() - 1);
    return bytes[i];
}
void ByteStream::operator<<(byte b) {
    writeByte(b);
}
uint ByteStream::size() const {
    return bytes.size();
}


Bytecode::Bytecode(ByteStream code) : code(code) {}
Opcode Bytecode::nextOpcode() {
    Opcode result = code.readOpcode(pc);
    pc++;
    return result;
}
clint Bytecode::nextInt() {
    clint result = code.readInt(pc);
    pc += 8;
    return result;
}
byte Bytecode::nextByte() {
    byte result = code.readByte(pc);
    pc++;
    return result;
}

void Bytecode::resetHead() {
    pc = 0;
}
void Bytecode::setHead(uint pos) {
    if(pos >= code.size())
        throw ByteOutOfRangeException(pos, code.size() - 1);
    pc = pos;
}
void Bytecode::stepBack(uint amount) {
    // pc is a uint, so subtracting to below 0 will certainly have it above our bytecode size
    if(pc - amount >= code.size())
        throw ByteOutOfRangeException(pc - amount, code.size() - 1);
    pc -= amount;
}
void Bytecode::stepForward(uint amount) {
    if(pc + amount >= code.size())
        throw ByteOutOfRangeException(pc + amount, code.size() - 1);
    pc += amount;
}