//
// Created by jonwi on 10/14/2019.
//

#ifndef CLEOD_VIRTUALMACHINE_H
#define CLEOD_VIRTUALMACHINE_H

#include <stack>
#include <iostream>

#include "../MiddleEnd/Bytecode.h"

//  VirtualMachine will implement a stack<Data> which gets pushed to and consumed from to execute instructions
struct Data {
    DataType type;
    ByteStream data;
};

class ExecutionException {
private:
    std::string reason;
public:
    ExecutionException(std::string reason);
    const std::string &what() const;
};

class VirtualMachine {
private:
    Bytecode code;
    std::stack<Data> stack;

    //  All printing output goes here - later we will make this a reference to the GUI console
    std::ostream &out = std::cout;

    void pop(Data &d);
    Data pop();

    void pushLiteral(DataType dt); // push a literal on the stack
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

//  not a fan.
const static std::unordered_map<DataType, std::unordered_map<DataType, bool>> ARITHMETIC_ALLOWED_TABLE = {
        { DataType::INT,
                {{DataType::INT, true},
                    {DataType::DOUBLE, true}}
        },
        {DataType::DOUBLE,
                {{DataType::INT, true},
                    {DataType::DOUBLE, true}};
        }
};

#endif //CLEOD_VIRTUALMACHINE_H
