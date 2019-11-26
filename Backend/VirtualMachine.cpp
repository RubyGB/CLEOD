#include <iostream>
#include <algorithm>
#include "VirtualMachine.h"

ExecutionException::ExecutionException(std::string reason) : reason(reason) {}
std::string ExecutionException::what() const {
    return "CLEOD Virtual Machine encountered an error: " + reason;
}

VirtualMachine::VirtualMachine(Bytecode &code, std::ostream &output) : code(code), out(output) {}
void VirtualMachine::execute() {
    Opcode next;
    while(!code.atEnd()) {
        next = code.nextOpcode();
        //std::cout << "OPCODE: " + std::to_string((int)next) << std::endl;
        switch(next) {
            case Opcode::LITERAL:
                pushNextLiteral(); break;
            case Opcode::PRINT:
                print(pop()); break;
            case Opcode::ADD:
                add(); break;
            case Opcode::SUBTRACT:
                subtract(); break;
            case Opcode::MULTIPLY:
                multiply(); break;
            case Opcode::DIVIDE:
                divide(); break;
            case Opcode::LT:
                lt(); break;
            case Opcode::BNE:
                bne(); break;
            case Opcode::JMP:
                jmp(); break;
            case Opcode::ASSN:
                assn(); break;
            case Opcode::REASSN:
                reassn(); break;
            case Opcode::ENDARR:
                endarr(); break;
            default:
                throw ExecutionException("Unrecognized Opcode: " + std::to_string((int)next));
        }
    }

    //  Do GC (very trivial atm) to prevent memory leaks
    gc.cleanAll();
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
    StringObject *so;
    VarObject *vo;
    switch(dt) {
        case DataType::DOUBLE:
            stack.push(Data(code.nextDouble()));
            break;
        case DataType::STRING:
            so = new StringObject(code.nextString());
            gc.add(so);
            stack.push(Data(so));
            break;
        case DataType::BOOL:
            stack.push(Data(code.nextBool()));
            break;
        case DataType::VAR:
            //  comes with string as ID
            vo = varIDHashTable[code.nextString()];
            stack.push(*vo->data);
            break;
        default:
            break;
    }
}

void VirtualMachine::print(Data top) {
    StringObject *so;
    VarObject *vo;
    ArrayObject *ao;
    switch(top.type) {
        case DataType::DOUBLE:
            out << top.data.d << std::endl; break;
        case DataType::STRING:
            so = dynamic_cast<StringObject *>(top.data.o);
            out << so->s << std::endl;
            break;
        case DataType::BOOL:
            if(top.data.b)
                out << "true" << std::endl;
            else
                out << "false" << std::endl;
            break;
        case DataType::VAR:
            //  dereference data contained by variable and print
            vo = dynamic_cast<VarObject *>(top.data.o);
            print(*vo->data);
        case DataType::ARRAY:
            ao = dynamic_cast<ArrayObject *>(top.data.o);
            for(Data *d : ao->elements) {
                print(*d);
            }
        default:
            break;
    }
}

void VirtualMachine::add() {
    //  pop will get us the data in reverse order from how it was pushed - this doesn't matter for add, will for others.
    Data d2 = pop();
    Data d1 = pop();
    if(d1.type == DataType::DOUBLE && d2.type == DataType::DOUBLE) {
        double result = d1.data.d + d2.data.d;
        stack.push(Data(result));
    }
    else if(d1.type == DataType::STRING) {
        StringObject *so = dynamic_cast<StringObject *>(d1.data.o);
        concat(so, d2, [](std::string s1, std::string s2) { return s1 + s2; });
    }
    else if(d2.type == DataType::STRING) {
        StringObject *so = dynamic_cast<StringObject *>(d2.data.o);
        concat(so, d1, [](std::string s1, std::string s2) { return s2 + s1; });
    }
}

//  concat lambda determines how the two strings are concatenated - for our implementation, this just means a + b vs. b + a.
void VirtualMachine::concat(StringObject *so, Data &d, std::function<std::string (std::string, std::string)> concatLambda) {
    StringObject *cat;
    if(d.type == DataType::STRING) {
        StringObject *so2 = dynamic_cast<StringObject *>(d.data.o);
        cat = new StringObject(concatLambda(so->s, so2->s));
        //  need this, but it will cause issues with var->data recursion. we have memory leaks, albeit small ones.
        //gc.clean(so2);
    }
    if(d.type == DataType::DOUBLE) {
        cat = new StringObject(concatLambda(so->s, std::to_string(d.data.d)));
    }
    if(d.type == DataType::BOOL) {
        if(d.data.b)
            cat = new StringObject(concatLambda(so->s, "true"));
        else
            cat = new StringObject(concatLambda(so->s, "false"));
    }
    if(d.type == DataType::VAR) {
        VarObject *vo = dynamic_cast<VarObject *>(d.data.o);
        Data dobj = *vo->data;
        //  yay recursion!
        concat(so, dobj, concatLambda);
    }

    gc.clean(so);
    gc.add(cat);
    stack.push(Data(cat));
}
void VirtualMachine::subtract() {
    Data d2 = pop();
    Data d1 = pop();
    if(d1.type == DataType::DOUBLE && d2.type == DataType::DOUBLE) {
        double result = d1.data.d - d2.data.d;
        stack.push(Data(result));
    }
}
void VirtualMachine::multiply() {
    Data d2 = pop();
    Data d1 = pop();
    if(d1.type == DataType::DOUBLE && d2.type == DataType::DOUBLE) {
        double result = d1.data.d * d2.data.d;
        stack.push(Data(result));
    }
}
void VirtualMachine::divide() {
    Data d2 = pop();
    Data d1 = pop();
    if(d1.type == DataType::DOUBLE && d2.type == DataType::DOUBLE) {
        double result = d1.data.d / d2.data.d;
        stack.push(Data(result));
    }
}
void VirtualMachine::lt(){
    Data d2 = pop();
    Data d1 = pop();
    if (d1.type == DataType::DOUBLE && d2.type == DataType::DOUBLE){
        bool rslt = (d1.data.d < d2.data.d);
        stack.push(Data(rslt));
    }
}
void VirtualMachine::bne(){
    cluint jumpLoc = code.nextUint();
    Data d1 = pop();
    if (d1.type == DataType::BOOL){
        if (!d1.data.b){
            try {
                code.setHead(jumpLoc);
            } catch(ByteOutOfRangeException &be) {
                code.setEnd();
            }
        }
    }
}
void VirtualMachine::jmp() {
    cluint jumpLoc = code.nextUint();
    try {
        code.setHead(jumpLoc);
    } catch(ByteOutOfRangeException &be) {
        code.setEnd();
    }
}
void VirtualMachine::assn() {
    //  variable assignment
    //  assumes this was preceded by a push literal of the assigned data type
    VarObject *vo = new VarObject(new Data(pop()));
    gc.add(vo);
    varIDHashTable[code.nextString()] = vo;
}
void VirtualMachine::reassn() {
    //  variable reassignment
    //  stack should have new value on top
    Data d = pop();

    std::string id = code.nextString();
    auto var = varIDHashTable.find(id);
    if(var == varIDHashTable.end()) {
        throw ExecutionException("Attempted to reassign undeclared variable with identifier: " + id);
    }
    VarObject *vo = var->second;
    delete vo->data;
    vo->data = new Data(d);
}
void VirtualMachine::endarr() {
    //  pop all values off the stack, and add them to our array!
    ArrayObject *ao = new ArrayObject();
    gc.add(ao);

    while(!stack.empty()) {
        ao->elements.push_back(new Data(pop()));
    }
    std::reverse(ao->elements.begin(), ao->elements.end());

    stack.push(Data(ao));
}
void VirtualMachine::ind() {
    //  Opcode::IND is suffixed with int operand acting as array index.
    //      Comes AFTER array is pushed to the stack.
    ArrayObject *ao = dynamic_cast<ArrayObject *>(pop().data.o);

    int index = code.nextInt() % ao->elements.size();

    // unfinished
}