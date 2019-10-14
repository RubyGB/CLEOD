//
// Created by jonwi on 10/14/2019.
//

#ifndef CLEOD_VIRTUALMACHINE_H
#define CLEOD_VIRTUALMACHINE_H

#include <stack>

#include "../MiddleEnd/Bytecode.h"

//  VirtualMachine will implement a stack<Data> which gets pushed to and consumed from to execute instructions
struct Data {
    DataType type;
    ByteStream data;
};

class VirtualMachine {
private:
    std::stack<Data> stack;
public:

};


#endif //CLEOD_VIRTUALMACHINE_H
