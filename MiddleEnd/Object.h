#pragma once

#include <string>
#include <vector>
#include <memory>
//#include "../Backend/VirtualMachine.h"

//  Can't #include VirtualMachine.h because of cyclic referencing
struct Data;

//  Objects are stored on the heap.

enum class ObjectType {
    VAR, STRING, ARRAY
};
struct Object {
    ObjectType type;

    //  used for GC
    Object *prev = nullptr;
    Object *next = nullptr;

    Object(ObjectType t) : type(t) {}
    virtual ~Object() {}
};

//  public inheritance allows casting from derived instance to base
struct VarObject : public Object {
    Data *data;

    VarObject(Data *d) : Object(ObjectType::VAR), data(d) {}
};

struct StringObject : public Object {
    std::string s;

    StringObject(std::string _s) : Object(ObjectType::STRING), s(_s) {}
};

struct ArrayObject : public Object {
    std::vector<Data *> elements;

    ArrayObject() : Object(ObjectType::ARRAY) {}
};