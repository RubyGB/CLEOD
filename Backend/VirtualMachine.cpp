#include <iostream>
#include "VirtualMachine.h"

ExecutionException::ExecutionException(std::string reason) : reason(reason) {}
std::string ExecutionException::what() const {
    return "CLEOD Virtual Machine encountered an error: " + reason;
}

VirtualMachine::VirtualMachine(Bytecode &code) : code(code) {}
void VirtualMachine::execute() {
    while(!code.atEnd()) {
        switch(code.nextOpcode()) {
            case Opcode::LITERAL:
                pushNextLiteral(); break;
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
            default:
                break;
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

void VirtualMachine::pushNextLiteral() {
    DataType dt = code.nextDataType();
    switch(dt) {
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
    if(d1.type == DataType::DOUBLE && d1.type == DataType::DOUBLE) {
        double result = d1.data.readDouble(0) + d2.data.readDouble(0);
        stack.push({DataType::DOUBLE, ByteStream(result)});
    }
}
void VirtualMachine::subtract() {
    Data d2 = pop();
    Data d1 = pop();
    if(d1.type == DataType::DOUBLE && d1.type == DataType::DOUBLE) {
        double result = d1.data.readDouble(0) - d2.data.readDouble(0);
        stack.push({DataType::DOUBLE, ByteStream(result)});
    }
}
void VirtualMachine::multiply() {
    Data d2 = pop();
    Data d1 = pop();
    if(d1.type == DataType::DOUBLE && d1.type == DataType::DOUBLE) {
        double result = d1.data.readDouble(0) * d2.data.readDouble(0);
        stack.push({DataType::DOUBLE, ByteStream(result)});
    }
}
void VirtualMachine::divide() {
    Data d2 = pop();
    Data d1 = pop();
    if(d1.type == DataType::DOUBLE && d1.type == DataType::DOUBLE) {
        double result = d1.data.readDouble(0) / d2.data.readDouble(0);
        stack.push({DataType::DOUBLE, ByteStream(result)});
    }
}