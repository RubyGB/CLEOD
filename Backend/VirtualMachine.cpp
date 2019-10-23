#include <iostream>
#include "VirtualMachine.h"

ExecutionException::ExecutionException(std::string reason) : reason(reason) {}
const std::string &ExecutionException::what() const {
    return "CLEOD Virtual Machine encountered an error: " + reason;
}

VirtualMachine::VirtualMachine(Bytecode &code) : code(code) {}
void VirtualMachine::execute() {
    while(!code.atEnd()) {
        switch(code.nextOpcode()) {
            case Opcode::LITERAL:
                pushLiteral(code.nextDataType()); break;
            case Opcode::PRINT:
                print(); break;
            case Opcode::ADD:
                add(); break;
            case Opcode::SUBTRACT:
                subtract(); break;
            case Opcode::MULTIPLY:
                multiply(); break;
            case Opcode::DIVIDE:
                divide(); break;
        }
    }
}

void VirtualMachine::pop(Data &d) {
    d = stack.top();
    stack.pop();
}
Data VirtualMachine::pop() {
    Data d;
    pop(d);
    return d;
}

void VirtualMachine::pushLiteral(DataType dt) {
    switch(dt) {
        case DataType::INT:
            stack.push({dt, ByteStream(code.nextInt())});
            break;
        case DataType::DOUBLE:
            stack.push({dt, ByteStream(code.nextDouble())});
            break;
        default:
            break;
    }
}

void VirtualMachine::print() {
    Data top = pop();
    switch(top.type) {
        case DataType::INT:
            out << top.data.readInt(0) << std::endl; break;
        case DataType::DOUBLE:
            out << top.data.readDouble(0) << std::endl; break;
        default:
            break;
    }
}

void VirtualMachine::add() {
    //  pop will get us the data in reverse order from how it was pushed - this doesn't matter for add, will for others.
    Data d2 = pop();
    Data d1 = pop();
    if(ARITHMETIC_ALLOWED_TABLE.at(d1.type).at(d2.type)) {

    }
    else {
        throw ExecutionException("Attempted to perform illegal arithmetic.");
    }
}