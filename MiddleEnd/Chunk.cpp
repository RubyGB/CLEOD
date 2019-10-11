//
// Created by jonwi on 10/9/2019.
//

#include "Chunk.h"

#include <iostream>
#include <string>

ByteOutOfRangeException::ByteOutOfRangeException(uint where, uint max) : where(where), max(max) {}
std::string ByteOutOfRangeException::what() const {
    return "Attempted to access byte " + std::to_string(where) + " when maximum byte was " + std::to_string(max) + ".";
}
OperationOutOfRangeException::OperationOutOfRangeException(uint where, uint max) : where(where), max(max) {}
std::string OperationOutOfRangeException::what() const {
    return "Attempted to access operation " + std::to_string(where) + " when maximum op was " + std::to_string(max) + ".";
}

const uint64_t BYTE_MASK = 0xFF;

clint LiteralByteStream::readInt(uint pos) const {
    ClintByteMask cbm = {0};
    for(uint end = pos + 8; pos < end; pos++) {
        if(pos >= bytes.size())
            throw ByteOutOfRangeException(pos, bytes.size() - 1);
        cbm.b[(8 - end) + pos] = bytes[pos];
    }
    return cbm.c;
}
void LiteralByteStream::writeInt(clint val) {
    for(int j = 0; j < 8; j++) {
        bytes.push_back((val & (BYTE_MASK << 8 * j)) >> 8 * j);
    }
}
cluint LiteralByteStream::readUint(uint pos) const {
    CluintByteMask cbm = {0};
    for(uint end = pos + 8; pos < end; pos++) {
        if(pos >= bytes.size())
            throw ByteOutOfRangeException(pos, bytes.size() - 1);
        cbm.b[(8 - end) + pos] = bytes[pos];
    }
    return cbm.c;
}
void LiteralByteStream::writeUint(cluint val) {
    for(int j = 0; j < 8; j++)
        bytes.push_back((val & (BYTE_MASK << 8 * j)) >> 8 * j);
}
byte LiteralByteStream::readByte(uint pos) const {
    if(pos >= bytes.size())
        throw ByteOutOfRangeException(pos, bytes.size() - 1);
    return bytes[pos];
}
void LiteralByteStream::writeByte(byte val) {
    bytes.push_back(val);
}
double LiteralByteStream::readDouble(uint pos) const {
    DoubleByteMask dbm = {0};
    for(uint end = pos + 8; pos < end; pos++) {
        if(pos >= bytes.size())
            throw ByteOutOfRangeException(pos, bytes.size() - 1);
        dbm.b[(8 - end) + pos] = bytes[pos];
    }
    return dbm.d;
}
void LiteralByteStream::writeDouble(double val) {
    DoubleByteMask dbm = {val};
    for(int j = 0; j < 8; j++)
        bytes.push_back(dbm.b[j]);
}
bool LiteralByteStream::readBool(uint pos) const {
    if(pos >= bytes.size())
        throw ByteOutOfRangeException(pos, bytes.size() - 1);
    if(bytes[pos])
        return true;
    return false;
}
void LiteralByteStream::writeBool(bool val) {
    bytes.push_back(val ? 1 : 0);
}
std::string LiteralByteStream::readString(uint pos) const {
    //  Strings in bytecode are NULL-TERMINATED. So we go until we find a '\0' character or go out of bounds.
    //      Note that this is a really easy way to throw an exception or get spooky behaviour if there's no string at head.
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
void LiteralByteStream::writeString(std::string val) {
    for(char c : val)
        bytes.push_back(static_cast<byte>(c));
    bytes.push_back(static_cast<byte>('\0'));
}


const Operation &OperationByteStream::readOp() {
    if(head >= bytecode.size())
        throw OperationOutOfRangeException(head, bytecode.size() - 1);
    return bytecode[head++];
}
void OperationByteStream::writeOp(Operation op) {
    bytecode.push_back(op);
}
void OperationByteStream::resetHead() {
    head = 0;
}
void OperationByteStream::setHead(uint pos) {
    head = pos;
    if(head >= bytecode.size())
        throw OperationOutOfRangeException(head, bytecode.size() - 1);
}
void OperationByteStream::stepBack(uint amount) {
    head -= amount;
    // head is a uint, so subtracting to below 0 will certainly have it above our bytecode size
    if(head >= bytecode.size())
        throw OperationOutOfRangeException(head, bytecode.size() - 1);
}