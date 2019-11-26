#pragma once

#include <stack>
#include <functional>
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
    Data(ArrayObject *ao) : type(DataType::ARRAY), data(ao) {}
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
    void print(Data top); // pop the top value off the stack and print it using this function

    void add();
    void concat(StringObject *so, Data &d, std::function<std::string (std::string, std::string)> concatLambda);

    void subtract();
    void multiply();
    void divide();
    void lt();
    void bne();
    void jmp();
    void assn();
    void reassn();
    void endarr();
    void ind();

public:
    VirtualMachine(Bytecode &code, std::ostream &output);

    //  Executes the bytecode.
    void execute();
};