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
#include <vector>
#include "Data.h"
#define MAX_RUN 32000000
using namespace std;

class Interpreter {
private:
    vector<Data *> rstack;
    int sp; //Initially -1
    vector<int> fpstack;
    int fpsp; //Initially -1
    int pc; //Initially 0
    unsigned char* mem;
    int size;
    bool halt_flag;
    int run_count;
    bool debug_flag;
public:
    Interpreter(unsigned char* input, int mem_size, bool flag);
    ~Interpreter();
    void run(); //Hopefully this will be our end run method
    void run_demo(); //This is to read through and check the memory
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
    void debug();
};
#endif /* Interpreter_h */
