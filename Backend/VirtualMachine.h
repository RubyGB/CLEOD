#pragma once

#include <stack>
#include <iostream>

#include "../MiddleEnd/Bytecode.h"
#include "../MiddleEnd/Object.h"
#include "GarbageCollector.h"

//  VirtualMachine will implement a stack<Data> which gets pushed to and consumed from to execute instructions
union DataValue {
    double d;
    bool b;
    Object *o;

    DataValue(double _d) : d(_d) {}
    DataValue(bool _b) : b(_b) {}
    DataValue(Object *_o) : o(_o) {}
};
struct Data {
    DataType type;
    DataValue data;

    Data() : type(DataType::INVALID), data(nullptr) {}
    Data(double d) : type(DataType::DOUBLE), data(d) {}
    Data(bool b) : type(DataType::BOOL), data(b) {}
    Data(Object *o) : type(DataType::VAR), data(o) {}
    Data(StringObject *so) : type(DataType::STRING), data(so) {}
};

class ExecutionException {
private:
    std::string reason;
public:
    ExecutionException(std::string reason);
    std::string what() const;
};

class VirtualMachine {
private:
    Bytecode code;
    std::stack<Data> stack;
    GarbageCollector gc;
    std::unordered_map<std::string, VarObject *> varIDHashTable;

    //  All printing output goes here - later we will make this a reference to the GUI console
    std::ostream &out = std::cout;

    void pop(Data &d);
    Data pop();

    void pushNextLiteral(); // push from bytecode
    void print(); // pop the top value off the stack and print it

    void add();
    void subtract();
    void multiply();
    void divide();
    void lt();
    void bne();
    void jmp();

public:
    VirtualMachine(Bytecode &code);

    //  Executes the bytecode.
    void execute();
};
