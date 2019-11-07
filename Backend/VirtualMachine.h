#pragma once

#include <stack>
#include <iostream>

#include "../MiddleEnd/Bytecode.h"
#include "../MiddleEnd/Object.h"

//  VirtualMachine will implement a stack<Data> which gets pushed to and consumed from to execute instructions
union DataValue {
    double d;
    bool b;
    Object *o;
};
struct Data {
    DataType type;
    DataValue data;
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
public:
    VirtualMachine(Bytecode &code);

    //  Executes the bytecode.
    void execute();
};
