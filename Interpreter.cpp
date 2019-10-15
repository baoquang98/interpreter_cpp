//
//  Interpreter.cpp
//  project 1
//
//  Created by Caszandra Strider on 10/14/19.
//  Copyright © 2019 Caszandra Strider. All rights reserved.
//

#include "Interpreter.h"
#include <array>

Interpreter::Interpreter(unsigned char* input) {
    mem = input;
    sp = -1;
    fpsp = -1;
    pc = 0;
}
Interpreter::~Interpreter() {}

void Interpreter::cmpe() {
    rstack[sp-1] = rstack[sp-1] == rstack[sp];
    sp--;
}

void Interpreter::cmplt() {
    rstack[sp-1] = rstack[sp-1] < rstack[sp];
    sp--;
}

void Interpreter::cmpgt() {
    rstack[sp-1] = rstack[sp-1] > rstack[sp];
    sp--;
}

void Interpreter::jmp() {
    pc = rstack[sp];
    sp = sp-1;
}

void Interpreter::jmpc() {
    if (rstack[sp-1]) {
        pc = rstack[sp];
    }
    sp = sp-2;
}

void Interpreter::call() {
    fpstack[++fpsp] = sp - rstack[sp];
    sp--;
    pc = rstack[sp--];
}

void Interpreter::ret() {
    sp = fpstack[fpsp--];
    pc = rstack[sp];
}

void Interpreter::pushc() {
    rstack[++sp] = mem[pc+1];
    pc += 2;
}

void Interpreter::pushs() {
    //TODO: FIXME
    short s = short(mem[pc+1] << 8  | mem[pc+2]);//FIXME
    rstack[++sp] = s;
    pc += 3;
}

void Interpreter::pushi() {
    //TODO: FIXME
    //byte[] bytes = {mem[pc+1], mem[pc+2], mem[pc+3], mem[pc+4]};
    int i = int(mem[pc+1] << 24  | mem[pc+2] << 16 | mem[pc+2] << 8 | mem[pc+2]); //FIXME
    rstack[++sp] = i;
    pc += 5;
}

void Interpreter::pushf() {
    //TODO: FIXME
    //byte[] bytes = {mem[pc+1], mem[pc+2], mem[pc+3], mem[pc+4]};
    float f = int(mem[pc+1] << 24  | mem[pc+2] << 16 | mem[pc+2] << 8 | mem[pc+2]);
    rstack[++sp] = f;
    pc += 5;
}

void Interpreter::pushvc() {
    rstack[sp] = rstack[rstack[sp]]; //TODO: sp++?
}

void Interpreter::pushvs() {
    rstack[sp] = rstack[rstack[sp]];
}

void Interpreter::pushvi() {
    rstack[sp] = rstack[rstack[sp]];
}

void Interpreter::pushvf() {
    rstack[sp] = rstack[rstack[sp]];
}

void Interpreter::popm() {
    sp -= rstack[sp];
}

void Interpreter::popv() {
    rstack[rstack[sp]] = rstack[sp-1];
    sp -= 2;
}

void Interpreter::popa() {
    int i = 0;
    for(i = 1; i < /*TODO*/; i++) {
        rstack[fpstack[fpsp] + i] = rstack[sp - rstack[sp] + (i - 1)];
    }
    rstack[fpstack[fpsp] + rstack[sp]] = rstack[sp-1];
    sp = fpstack[fpsp]+rstack[sp];
}

void Interpreter::peekc() {
    rstack[fpstack[fpsp] + rstack[sp-1]+1] = rstack[fpstack[fpsp]+rstack[sp]+1];
}

void Interpreter::peeks() {
    rstack[fpstack[fpsp] + rstack[sp-1]+1] = rstack[fpstack[fpsp]+rstack[sp]+1];
}

void Interpreter::peeki() {
    rstack[fpstack[fpsp] + rstack[sp-1]+1] = rstack[fpstack[fpsp]+rstack[sp]+1];
}

void Interpreter::peekf() {
    rstack[fpstack[fpsp] + rstack[sp-1]+1] = rstack[fpstack[fpsp]+rstack[sp]+1];
}

void Interpreter::pokec() {
    rstack[fpstack[fpsp] + rstack[sp]+1] = rstack[fpstack[fpsp] + rstack[sp-1]+1];
}

void Interpreter::pokes() {
    rstack[fpstack[fpsp] + rstack[sp]+1] = rstack[fpstack[fpsp] + rstack[sp-1]+1];
}

void Interpreter::pokei() {
    rstack[fpstack[fpsp] + rstack[sp]+1] = rstack[fpstack[fpsp] + rstack[sp-1]+1];
}

void Interpreter::pokef() {
    rstack[fpstack[fpsp] + rstack[sp]+1] = rstack[fpstack[fpsp] + rstack[sp-1]+1];
}

void Interpreter::swp() {
    tmp = rstack[sp-1];
    rstack[sp-1] = rstack[sp];
    rstack[sp] = tmp;
}

void Interpreter::add() {
    rstack[sp-1] = rstack[sp-1] + rstack[sp];
    sp--;
}

void Interpreter::sub() {
    rstack[sp-1] = rstack[sp-1] - rstack[sp];
    sp--;
}

void Interpreter::mul() {
    rstack[sp-1] = rstack[sp-1] * rstack[sp];
    sp--;
}

void Interpreter::div() {
    rstack[sp-1] = rstack[sp-1] / rstack[sp];
    sp--;
}

void Interpreter::printc() {
    System.out.println(rstack[sp--]);
}

void Interpreter::prints() {
    System.out.println(rstack[sp--]);
}

void Interpreter::printi() {
    System.out.println(rstack[sp--]);
}

void Interpreter::halt() {
    //TODO:Terminate,
    //TODO:fix up these
    System.out.println(pc);
    System.out.println(sp);
    if (rstack) {//TODO: Need more specifications?
        System.out.println(rstack);
    }
    else {
        System.out.println("empty.\n");//CORRECT?
    }
    System.out.println(fpsp);
    if (fpstack) {//TODO: Need more specifications?
        System.out.println(fpstack);
    }
    else {
        System.out.println("empty.\n");//CORRECT?
    }
    //    default : //TODO: Need a default?
}

void Interpreter::run() {
    int size = sizeof(mem)/sizeof(mem);
    for(int i = 0; i < size; i) {
        switch (mem[i]) {
        //Comparison Bytecodes
            case 10000100://(132 || 10000100)://cmpe
                cmpe();
            case 10001000://(136 || 10001000)://cmplt
                cmplt();
            case 10001100://(140 || 10001100)://cmpgt
                cmpgt();
        //Control Flow Bytecodes
            case 00100100://(36 || 00100100): //jmp
                jmp();
            case 00101000://(40 || 00101000): //jmpc
                jmpc();
            case 00101100://(44 || 00101100): //call
                call();
            case 00110000://(48 || 00110000): //ret
                ret();
        //Stack Manipulation Byte Codes
            case 01000100://(68 || 01000100): //pushc
                pushc();
            case 01000101://(69 || 01000101): //pushs
                pushs();
            case 01000110://(70 || 01000110): //pushi
                pushi();
            case 01000111://(71 || 01000111): //pushf
                pushf();
            case 01001000://(72 || 01001000): //pushvc
                pushvc();
            case 01001001://(73 || 01001001): //pushvs
                pushvs();
            case 01001010://(74 || 01001010): //pushvi
                pushvi();
            case 01001011://(75 || 01001011): //pushvf
                pushvf();
            case 01001100://(76 || 01001100): //popm
                popm();
            case 01010000://(80 || 01010000): //popv
                popv();
            case 01001101://(77 || 01001101): //popa
                popa();
            case 01011000://(84 || 01011000): //peekc
                peekc();
            case 01011001://(85 || 01011001): //peeks
                peeks();
            case 01011010://(86 || 01011010): //peeki
                peeki();
            case 01011011://(87 || 01011011): //peekf
                peekf();
            case 01100000://(88 || 01100000): //pokec
                pokec();
            case 01100001://(89 || 01100001): //pokes
                pokes();
            case 01100010://(90 || 01100010): //pokei
                pokei();
            case 01100011://(91 || 01100011): //pokef
                pokef();
            case 01100100://(94 || 01100100): //swp
                swp();
        //Arithmetic Byte Codes
            case 01100100://(100 || 01100100): //add
                add();
            case 01101000://(104 || 01101000): //sub
                sub();
            case 01101100://(108 || 01101100): //mul
                mul();
            case 01110000://(112 || 01110000): //div
                div();
        //Special Op Codes
            case 10010100://(148 || 10010100): //printc
                printc();
            case 10010101://(149 || 10010101): //prints
                prints();
            case 10010110://(150 || 10010110): //printi
                printi();
            case 00000000://(0 || 00000000): //halt
                halt();
        }
    }
}
