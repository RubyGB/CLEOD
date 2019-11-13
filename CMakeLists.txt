cmake_minimum_required(VERSION 3.14)
project(CLEOD)

set(CMAKE_CXX_STANDARD 14)

add_executable(CLEOD main.cpp Frontend/Token.cpp Frontend/Token.h Frontend/Scanner.cpp Frontend/Scanner.h MiddleEnd/Bytecode.cpp MiddleEnd/Bytecode.h MiddleEnd/Compiler.cpp MiddleEnd/Compiler.h Backend/VirtualMachine.cpp Backend/VirtualMachine.h MiddleEnd/Object.h Backend/GarbageCollector.cpp Backend/GarbageCollector.h)