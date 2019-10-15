//
//  Interpreter.h
//  project 1
//
//  Created by Caszandra Strider on 10/14/19.
//  Copyright © 2019 Caszandra Strider. All rights reserved.
//

#ifndef Interpreter_h
#define Interpreter_h

#include <stdio.h>
#include <cstdint>

class Interpreter {
private:
    int* rstack; //TODO:type. I said int* but I don't know what it is
    int sp; //Initially -1
    int* fpstack; //TODO:type. I said int* but I don't know what it is
    int fpsp; //Initially -1
    int pc; //Initially 0
    uint8_t* mem; //Work on intialization
public:
    Interpreter();
    ~Interpreter();
    void run(uint8_t* mem);
    //Comparison Bytecodes
    void cmpe();
    void cmplt();
    void cmpgt();
    //Control Flow Bytecodes
    void jmp();
    void jmpc();
    void call();
    void ret();
    //Stack Manipulation Byte Codes
    void pushc();
    void pushs();
    void pushi();
    void pushf();
    void pushvc();
    void pushvs();
    void pushvi();
    void pushvf();
    void popm();
    void popv();
    void popa();
    void peekc();
    void peeks();
    void peeki();
    void peekf();
    void pokec();
    void pokes();
    void pokei();
    void pokef();
    void swp();
    //Arithmetic Byte Codes
    void add();
    void sub();
    void mul();
    void div();
    //Special Op Codes
    void printc();
    void prints();
    void printi();
    void printf();
    void halt();
};
#endif /* Interpreter_h */
