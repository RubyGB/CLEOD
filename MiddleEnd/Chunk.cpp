//
// Created by jonwi on 10/9/2019.
//

#include "Chunk.h"

#include <iostream>
#include <string>

ByteOutOfRangeException::ByteOutOfRangeException(uint where, uint max) : where(where), max(max) {}
std::string ByteOutOfRangeException::what() {
    return "Attempted to access byte " + std::to_string(where) + " when maximum byte was " + std::to_string(max) + ".";
}

const uint64_t BYTE_MASK = 0xFF;

clint LiteralByteStream::readInt() {
    ClintByteMask cbm = {0};
    for(uint end = head + 8; head < end; head++) {
        if(head >= bytes.size())
            throw ByteOutOfRangeException(head, bytes.size() - 1);
        cbm.b[(8 - end) + head] = bytes[head];
    }
    return cbm.c;
}
void LiteralByteStream::writeInt(clint val) {
    for(int j = 0; j < 8; j++) {
        bytes.push_back((val & (BYTE_MASK << 8 * j)) >> 8 * j);
    }
}
cluint LiteralByteStream::readUint() {
    CluintByteMask cbm = {0};
    for(uint end = head + 8; head < end; head++) {
        if(head >= bytes.size())
            throw ByteOutOfRangeException(head, bytes.size() - 1);
        cbm.b[(8 - end) + head] = bytes[head];
    }
    return cbm.c;
}
void LiteralByteStream::writeUint(cluint val) {
    for(int j = 0; j < 8; j++)
        bytes.push_back((val & (BYTE_MASK << 8 * j)) >> 8 * j);
}
byte LiteralByteStream::readByte() {
    if(head >= bytes.size())
        throw ByteOutOfRangeException(head, bytes.size() - 1);
    return bytes[head++];
}
void LiteralByteStream::writeByte(byte val) {
    bytes.push_back(val);
}
double LiteralByteStream::readDouble() {
    DoubleByteMask dbm = {0};
    for(uint end = head + 8; head < end; head++) {
        if(head >= bytes.size())
            throw ByteOutOfRangeException(head, bytes.size() - 1);
        dbm.b[(8 - end) + head] = bytes[head];
    }
    return dbm.d;
}
void LiteralByteStream::writeDouble(double val) {
    DoubleByteMask dbm = {val};
    for(int j = 0; j < 8; j++)
        bytes.push_back(dbm.b[j]);
}
bool LiteralByteStream::readBool() {
    if(head >= bytes.size())
        throw ByteOutOfRangeException(head, bytes.size() - 1);
    if(bytes[head++])
        return true;
    return false;
}
void LiteralByteStream::writeBool(bool val) {
    bytes.push_back(val ? 1 : 0);
}
std::string LiteralByteStream::readString() {
    //  Strings in bytecode are NULL-TERMINATED. So we go until we find a '\0' character or go out of bounds.
    //      Note that this is a really easy way to throw an exception or get spooky behaviour if there's no string at head.
    //      Also note that since most clints will have plenty of empty bytes, this will probably not throw error in most cases.
    char c;
    std::string result = "";
    if(head >= bytes.size())
        throw ByteOutOfRangeException(head, bytes.size() - 1);
    while((c = static_cast<char>(bytes[head++])) != '\0') {
        if(head >= bytes.size())
            throw ByteOutOfRangeException(head, bytes.size() - 1);
        result += c;
    }
    return result;
}
void LiteralByteStream::writeString(std::string val) {
    for(char c : val)
        bytes.push_back(static_cast<byte>(c));
    bytes.push_back(static_cast<byte>('\0'));
}

void LiteralByteStream::resetHead() {
    head = 0;
}
void LiteralByteStream::setHead(uint pos) {
    if(pos >= bytes.size())
        throw ByteOutOfRangeException(pos, bytes.size() - 1);
    head = pos;
}
void LiteralByteStream::stepBack(uint amount) {
    head -= amount;
}