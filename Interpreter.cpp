//
//  Interpreter.cpp
//  project 1
//
//  Created by Caszandra Strider on 10/14/19.
//  Copyright © 2019 Caszandra Strider. All rights reserved.
//

#include "Interpreter.h"
#include <array>
#include <iostream>

Interpreter::Interpreter(unsigned char* input, int mem_size) {
    mem = input;
    sp = -1;
    fpsp = -1;
    pc = 0;
    size = mem_size;
}

Interpreter::~Interpreter() {}

void Interpreter::cmpe() {
    std::cout << "cmpe" <<std::endl;
    //rstack[sp-1] = rstack[sp-1] == rstack[sp];
    sp--;
    pc++;
}

void Interpreter::cmplt() {
    std::cout << "cmplt" <<std::endl;
    //rstack[sp-1] = rstack[sp-1] < rstack[sp];
    sp--;
    pc++;
}

void Interpreter::cmpgt() {
    std::cout << "cmpgt" <<std::endl;
    //rstack[sp-1] = rstack[sp-1] > rstack[sp];
    sp--;
    pc++;
}

void Interpreter::jmp() {
    std::cout << "jmp" <<std::endl;
    //pc = rstack[sp];
    sp = sp-1;
}

void Interpreter::jmpc() {
    std::cout << "jmpc" <<std::endl;
    //if (rstack[sp-1]) {
    //    pc = rstack[sp];
    //}
    sp = sp-2;
}

void Interpreter::call() {
    std::cout << "call" <<std::endl;
    //fpstack[++fpsp] = sp - rstack[sp];
    sp--;
    //pc = rstack[sp--];
}

void Interpreter::ret() {
    std::cout << "ret" <<std::endl;
    //sp = fpstack[fpsp--];
    //pc = rstack[sp];
}

void Interpreter::pushc() {
    std::cout << "pushc" <<std::endl;
    //rstack[++sp] = mem[pc+1];
    pc += 2;
}

void Interpreter::pushs() {
    std::cout << "cmpe" <<std::endl;
    //TODO: FIXME
    short s = short(mem[pc+1] << 8  | mem[pc+2]);
    //rstack[++sp] = s;
    pc += 3;
}

void Interpreter::pushi() {
    std::cout << "pushi" <<std::endl;
    //TODO: FIXME
    int i = int(mem[pc+1] << 24  | mem[pc+2] << 16 | mem[pc+2] << 8 | mem[pc+2]);
    //rstack[++sp] = i;
    pc += 5;
}

void Interpreter::pushf() {
    std::cout << "pushf" <<std::endl;
    //TODO: FIXME
    //byte[] bytes = {mem[pc+1], mem[pc+2], mem[pc+3], mem[pc+4]};
    float f = float(mem[pc+1] << 24  | mem[pc+2] << 16 | mem[pc+2] << 8 | mem[pc+2]);
    //rstack[++sp] = f;
    pc += 5;
}

void Interpreter::pushvc() {
    std::cout << "pushvc" <<std::endl;
    //rstack[sp] = rstack[fpstack[fpsp] + rstack[sp] + 1]; //TODO: sp++?
    pc++;
}

void Interpreter::pushvs() {
    std::cout << "pushvs" <<std::endl;
    //rstack[sp] = rstack[fpstack[fpsp] + rstack[sp] + 1];
    pc++;
}

void Interpreter::pushvi() {
    std::cout << "pushvi" <<std::endl;
    //rstack[sp] = rstack[fpstack[fpsp] + rstack[sp] + 1];
    pc++;
}

void Interpreter::pushvf() {
    std::cout << "pushvf" <<std::endl;
    //rstack[sp] = rstack[fpstack[fpsp] + rstack[sp] + 1];
    pc++;
}

void Interpreter::popm() {
    std::cout << "popm" <<std::endl;
    //sp -= rstack[sp];
    pc++;
}

void Interpreter::popv() {
    std::cout << "popv" <<std::endl;
   // rstack[fpstack[fpsp] + int(rstack[sp]) + 1] = rstack[sp-1];
    sp -= 2;
    pc++;
}

void Interpreter::popa() {
    std::cout << "popa" <<std::endl;
    // WHAT THE HELL IS THIS FUNCTION??
    /*int i = 0;
    for(i = 1; i < TODO; i++) {
        rstack[fpstack[fpsp] + i] = rstack[sp - rstack[sp] + (i - 1)];
    }
    rstack[fpstack[fpsp] + rstack[sp]] = rstack[sp-1];
    sp = fpstack[fpsp]+rstack[sp];*/
    pc++;
}

void Interpreter::peekc() {
    std::cout << "cmpe" <<std::endl;
 //   rstack[fpstack[fpsp] + rstack[sp-1]+1] = rstack[fpstack[fpsp]+rstack[sp]+1];
    pc++;
}

void Interpreter::peeks() {
    std::cout << "peeks" <<std::endl;
  //  rstack[fpstack[fpsp] + rstack[sp-1]+1] = rstack[fpstack[fpsp]+rstack[sp]+1];
    pc++;
}

void Interpreter::peeki() {
    std::cout << "peeki" <<std::endl;
    pc++;
  //  rstack[fpstack[fpsp] + rstack[sp-1]+1] = rstack[fpstack[fpsp]+rstack[sp]+1];
}

void Interpreter::peekf() {
    std::cout << "peekf" <<std::endl;
    pc++;
  //  rstack[fpstack[fpsp] + rstack[sp-1]+1] = rstack[fpstack[fpsp]+rstack[sp]+1];
}

void Interpreter::pokec() {
    std::cout << "pokec" <<std::endl;
    pc++;
  //  rstack[fpstack[fpsp] + rstack[sp]+1] = rstack[fpstack[fpsp] + rstack[sp-1]+1];
}

void Interpreter::pokes() {
    std::cout << "pokes" <<std::endl;
    pc++;
   // rstack[fpstack[fpsp] + rstack[sp]+1] = rstack[fpstack[fpsp] + rstack[sp-1]+1];
}

void Interpreter::pokei() {
    std::cout << "pokei" <<std::endl;
    pc++;
  //  rstack[fpstack[fpsp] + rstack[sp]+1] = rstack[fpstack[fpsp] + rstack[sp-1]+1];
}

void Interpreter::pokef() {
    std::cout << "pokef" <<std::endl;
    pc++;
  //  rstack[fpstack[fpsp] + rstack[sp]+1] = rstack[fpstack[fpsp] + rstack[sp-1]+1];
}

void Interpreter::swp() {
    std::cout << "swp" <<std::endl;
    pc++;
    /*tmp = rstack[sp-1];
    rstack[sp-1] = rstack[sp];
    rstack[sp] = tmp;*/
}

void Interpreter::add() {
    std::cout << "add" <<std::endl;
//    rstack[sp-1] = rstack[sp-1] + rstack[sp];
    sp--;
    pc++;
}

void Interpreter::sub() {
    std::cout << "sub" <<std::endl;
//    rstack[sp-1] = rstack[sp-1] - rstack[sp];
    sp--;
    pc++;
}

void Interpreter::mul() {
    std::cout << "mul" <<std::endl;
//    rstack[sp-1] = rstack[sp-1] * rstack[sp];
    sp--;
    pc++;
}

void Interpreter::div() {
    std::cout << "div" <<std::endl;
 //   rstack[sp-1] = rstack[sp-1] / rstack[sp];
    sp--;
    pc++;
}

void Interpreter::printc() {
    std::cout << "printc" <<std::endl;
//    std::cout <<rstack[sp--] << std::endl;
    pc++;
}

void Interpreter::prints() {
    std::cout << "prints" <<std::endl;
    pc++;
 //   std::cout <<rstack[sp--]<< std::endl;
}

void Interpreter::printi() {
    std::cout << "printi" <<std::endl;
    pc++;
//    std::cout <<rstack[sp--]<< std::endl;
}

void Interpreter::printf() {
    std::cout << "printf" <<std::endl;
    pc++;
//    std::cout <<rstack[sp--]<< std::endl;
}

void Interpreter::halt() {
    /*std::cout << "halt" <<std::endl;
    //TODO:Terminate,
    //TODO:fix up these
    std::cout <<pc<< std::endl;
    std::cout <<sp<< std::endl;
    //TODO: Print out rstack
    for (int i = 0; i < rstack.size(); i++) {
        std::cout << rstack[i] << std::endl;
    }
    
    std::cout <<fpsp<< std::endl;
    for (int i = 0; i < rstack.size(); i++) {
        std::cout << rstack[i] << std::endl;
    }
    std::cout <<"Last instructions?"<< std::endl; */
}

void Interpreter::run() {
    for(int i = 0; i < size; i++) {
        std::cout << (int) mem[i] <<" ";
        switch (mem[i]) {
        //Comparison Bytecodes
            case 132://(132 || 10000100)://cmpe
                cmpe();
                break;
            case 136://(136 || 10001000)://cmplt
                cmplt();
                break;
            case 140://(140 || 10001100)://cmpgt
                cmpgt();
                break;
        //Control Flow Bytecodes
            case 36://(36 || 00100100): //jmp
                jmp();
                break;
            case 40://(40 || 00101000): //jmpc
                jmpc();
                break;
            case 44://(44 || 00101100): //call
                call();
                break;
            case 48://(48 || 00110000): //ret
                ret();
                break;
        //Stack Manipulation Byte Codes
            case 68://(68 || 01000100): //pushc
                pushc();
                break;
            case 69://(69 || 01000101): //pushs
                pushs();
                break;
            case 70://(70 || 01000110): //pushi
                pushi();
                break;
            case 71://(71 || 01000111): //pushf
                pushf();
                break;
            case 72://(72 || 01001000): //pushvc
                pushvc();
                break;
            case 73://(73 || 01001001): //pushvs
                pushvs();
                break;
            case 74://(74 || 01001010): //pushvi
                pushvi();
                break;
            case 75://(75 || 01001011): //pushvf
                pushvf();
                break;
            case 76://(76 || 01001100): //popm
                popm();
                break;
            case 80://(80 || 01010000): //popv
                popv();
                break;
            case 77://(77 || 01001101): //popa
                popa();
                break;
            case 84://(84 || 01011000): //peekc
                peekc();
                break;
            case 85://(85 || 01011001): //peeks
                peeks();
                break;
            case 86://(86 || 01011010): //peeki
                peeki();
                break;
            case 87://(87 || 01011011): //peekf
                peekf();
                break;
            case 88://(88 || 01100000): //pokec
                pokec();
                break;
            case 89://(89 || 01100001): //pokes
                pokes();
                break;
            case 90://(90 || 01100010): //pokei
                pokei();
                break;
            case 91://(91 || 01100011): //pokef
                pokef();
                break;
            case 94://(94 || 01100100): //swp
                swp();
                break;
        //Arithmetic Byte Codes
            case 110://(100 || 01100100): //add
                add();
                break;
            case 104://(104 || 01101000): //sub
                sub();
                break;
            case 108://(108 || 01101100): //mul
                mul();
                break;
            case 112://(112 || 01110000): //div
                div();
                break;
        //Special Op Codes
            case 144://(148 || 10010100): //printc
                printc();
                break;
            case 145://(149 || 10010101): //prints
                prints();
                break;
            case 146://(150 || 10010110): //printi
                printi();
                break;
            case 147://(150 || 10010110): //printi
                printf();
                break;
            case 0://(0 || 00000000): //halt
                halt();
                break;
            default:
                cout <<"Unknown inst, Hex: " << hex << (int) mem[i] << dec << endl;
        }
    }
}
