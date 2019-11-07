#pragma once

//  Can't #include VirtualMachine.h because of cyclic referencing
struct Data;

//  Objects are stored on the heap.

enum class ObjectType {
    VAR
};
struct Object {
    ObjectType type;

    //  used for GC
    Object *next;
};

//  public inheritance allows casting from derived instance to base
struct VarObject : public Object {
    Data *data;
};