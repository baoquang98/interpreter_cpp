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

Interpreter::Interpreter(unsigned char* input, int mem_size, bool flag) {
    mem = input;
    sp = -1;
    fpsp = -1;
    pc = 0;
    size = mem_size;
    halt_flag = false;
    run_count = 0;
    debug_flag = flag;
}

Interpreter::~Interpreter() {}

void Interpreter::debug() {
    if (!debug_flag){
        return;
    }
    cout << "pc: " << pc <<endl;
    cout << "sp: " << sp << endl;
    cout << "rstack: ";
    for (int i = 0; i < rstack.size(); i++) {
        switch(rstack[i]->type){
        case INT_TYPE:
            cout << rstack[i]->int_data << " ";
            break;
        case FLOAT_TYPE:
            cout << rstack[i]->float_data << " ";
            break;
        case CHAR_TYPE:
            cout <<(int) rstack[i]->char_data << " ";
            break;
        case SHORT_TYPE:
            cout << rstack[i]->short_data << " ";
            break;
        }
    }
    cout <<endl;
    cout << "fpsp: " << fpsp << endl;
    cout << "fpstack: ";
    for (int i = 0; i < fpstack.size(); i++) {
        cout << fpstack[i] << " ";
    }
    cout <<endl;
    cout << "---------------------------" <<endl;
}
void Interpreter::cmpe() {
    if (debug_flag){
        std::cout << "cmpe" <<std::endl;
    }
    
    switch (rstack[sp]->type) {
        case INT_TYPE:
            rstack[sp-1]->int_data = (rstack[sp-1]->int_data == rstack[sp]->int_data);
            break;
        case FLOAT_TYPE:
            rstack[sp-1]->float_data = (rstack[sp-1]->float_data == rstack[sp]->float_data);
            break;
        case CHAR_TYPE:
            rstack[sp-1]->char_data = (rstack[sp-1]->char_data == rstack[sp]->char_data);
            break;
        case SHORT_TYPE:
            rstack[sp-1]->short_data = (rstack[sp-1]->short_data == rstack[sp]->short_data);
            break;
    }
    rstack.pop_back();
    sp--;
    pc++;
    debug();
}

void Interpreter::cmplt() {
    if (debug_flag){
        std::cout << "cmplt" <<std::endl;
    }
    //rstack[sp-1] = rstack[sp-1] < rstack[sp];
    switch (rstack[sp]->type) {
        case INT_TYPE:
            rstack[sp-1]->int_data = (rstack[sp-1]->int_data < rstack[sp]->int_data);
            break;
        case FLOAT_TYPE:
            rstack[sp-1]->float_data = (rstack[sp-1]->float_data < rstack[sp]->float_data);
            break;
        case CHAR_TYPE:
            rstack[sp-1]->char_data = (rstack[sp-1]->char_data < rstack[sp]->char_data);
            break;
        case SHORT_TYPE:
            rstack[sp-1]->short_data = (rstack[sp-1]->short_data < rstack[sp]->short_data);
            break;
    }
    rstack.pop_back();
    sp--;
    pc++;
}

void Interpreter::cmpgt() {
    if (debug_flag){
        std::cout << "cmpgt" <<std::endl;
    }
    //rstack[sp-1] = rstack[sp-1] > rstack[sp];
    switch (rstack[sp]->type) {
        case INT_TYPE:
            rstack[sp-1]->int_data = (rstack[sp-1]->int_data > rstack[sp]->int_data);
            break;
        case FLOAT_TYPE:
            rstack[sp-1]->float_data = (rstack[sp-1]->float_data > rstack[sp]->float_data);
            break;
        case CHAR_TYPE:
            rstack[sp-1]->char_data = (rstack[sp-1]->char_data > rstack[sp]->char_data);
            break;
        case SHORT_TYPE:
            rstack[sp-1]->short_data = (rstack[sp-1]->short_data > rstack[sp]->short_data);
            break;
    }
    rstack.pop_back();
    sp--;
    pc++;
}

void Interpreter::jmp() {
    if (debug_flag){
        std::cout << "jmp" <<std::endl;
    }
    pc = rstack[sp]->int_data;
    rstack.pop_back();
    sp = sp-1;
}

void Interpreter::jmpc() {
    if (debug_flag){
        std::cout << "jmpc" <<std::endl;
    }
    if (rstack[sp-1]->int_data) {
        pc = rstack[sp]->int_data;
    } else {
        pc++;
    }//THis might need modification, as we're implying the top 2 element of the stack are 2 ints
    rstack.pop_back();
    rstack.pop_back();
    sp = sp-2;
    debug();
}

void Interpreter::call() {
    if (debug_flag){
        std::cout << "call" <<std::endl;
    }
    //fpstack[++fpsp] = sp - rstack[sp]->int_data - 1;
    switch (rstack[sp]->type) {
        case INT_TYPE:
            fpstack.push_back(sp - rstack[sp]->int_data - 1);
            break;
        case FLOAT_TYPE:
            fpstack.push_back(int(sp - rstack[sp]->float_data - 1));
            break;
        case CHAR_TYPE:
            fpstack.push_back(sp - rstack[sp]->char_data - 1);
            break;
        case SHORT_TYPE:
            fpstack.push_back(sp - rstack[sp]->short_data - 1);
            break;
    }
    sp--;
    fpsp++;
    rstack.pop_back();
    pc = rstack[sp--]->int_data;
    rstack.pop_back();
    debug();
}

void Interpreter::ret() {
    if (debug_flag){
        std::cout << "ret" <<std::endl;
    }
    sp = fpstack[fpsp--];
    //pc = rstack[sp--];
    switch (rstack[sp]->type) {
        case INT_TYPE:
            pc = rstack[sp--]->int_data;
            break;
        case FLOAT_TYPE:
            pc = int(rstack[sp--]->float_data);
            break;
        case CHAR_TYPE:
            pc = rstack[sp--]->char_data;
            break;
        case SHORT_TYPE:
            pc = rstack[sp--]->short_data;
            break;
    }
    rstack.pop_back();
    fpstack.pop_back();
    debug();
}

void Interpreter::pushc() {
    if (debug_flag){
        std::cout << "pushc" <<std::endl;
    }
    //rstack[++sp] = mem[pc+1];
    //char c = (char) mem[pc+1];
    unsigned char var[2] = {mem[pc+1]};
    char c;
    memcpy(&c, &var, sizeof(c));
    rstack.push_back(new Data(c));
    sp++;
    pc += 2;
    debug();
}

void Interpreter::pushs() {
    if (debug_flag){
        std::cout << "pushs" <<std::endl;
    }
    //TODO: FIXME
    //short s = short(mem[pc+2] << 8  | mem[pc+1]);
    //rstack[++sp] = s;
    unsigned char var[2] = {mem[pc+1], mem[pc+2]};
    short s;
    memcpy(&s, &var, sizeof(s));

    rstack.push_back(new Data(s));
    sp++;
    pc += 3;
}

void Interpreter::pushi() {
    if (debug_flag){
        std::cout << "pushi" <<std::endl;
    }
    //TODO: FIXME
    //int i = int(mem[pc+4] << 24  | mem[pc+3] << 16 | mem[pc+2] << 8 | mem[pc+1]);
    //rstack[++sp] = i;
    unsigned char var[4] = {mem[pc+1], mem[pc+2], mem[pc+3], mem[pc+4]};
    int i;
    memcpy(&i, &var, sizeof(i));
    
    rstack.push_back(new Data(i));
    sp++;
    pc += 5;
    debug();
}

void Interpreter::pushf() {
    if (debug_flag){
        std::cout << "pushf" <<std::endl;
    }
    //TODO: FIXME
    //byte[] bytes = {mem[pc+1], mem[pc+2], mem[pc+3], mem[pc+4]};
    //float f = float(mem[pc+4] << 24  | mem[pc+3] << 16 | mem[pc+2] << 8 | mem[pc+1]);
    //rstack[++sp] = f;
    unsigned char var[4] = {mem[pc+1], mem[pc+2], mem[pc+3], mem[pc+4]};
    float f;
    memcpy(&f, &var, sizeof(f));
    rstack.push_back(new Data(f));
    sp++;
    pc += 5;
}

void Interpreter::pushvc() {
    if (debug_flag){
        std::cout << "pushvc" <<std::endl;
    }
    //rstack[sp] = rstack[fpstack[fpsp] + rstack[sp] + 1]; //TODO: sp++?
    switch (rstack[sp]->type) {
        case INT_TYPE:
            rstack[sp]->int_data = rstack[fpstack[fpsp] + rstack[sp]->int_data + 1]->int_data;
            break;
        case FLOAT_TYPE:
            rstack[sp]->float_data = rstack[fpstack[fpsp] + rstack[sp]->float_data + 1]->float_data;
            break;
        case CHAR_TYPE:
            rstack[sp]->char_data = rstack[fpstack[fpsp] + rstack[sp]->char_data + 1]->char_data;
            break;
        case SHORT_TYPE:
            rstack[sp]->short_data = rstack[fpstack[fpsp] + rstack[sp]->short_data + 1]->short_data;
            break;
    }
    pc++;
}

void Interpreter::pushvs() {
    if (debug_flag){
        std::cout << "pushvs" <<std::endl;
    }
    //rstack[sp] = rstack[fpstack[fpsp] + rstack[sp] + 1];
    switch (rstack[sp]->type) {
        case INT_TYPE:
            rstack[sp]->int_data = rstack[fpstack[fpsp] + rstack[sp]->int_data + 1]->int_data;
            break;
        case FLOAT_TYPE:
            rstack[sp]->float_data = rstack[fpstack[fpsp] + rstack[sp]->float_data + 1]->float_data;
            break;
        case CHAR_TYPE:
            rstack[sp]->char_data = rstack[fpstack[fpsp] + rstack[sp]->char_data + 1]->char_data;
            break;
        case SHORT_TYPE:
            rstack[sp]->short_data = rstack[fpstack[fpsp] + rstack[sp]->short_data + 1]->short_data;
            break;
    }
    pc++;
}

void Interpreter::pushvi() {
    if (debug_flag){
        std::cout << "pushvi" <<std::endl;
    }
    //rstack[sp] = rstack[fpstack[fpsp] + rstack[sp] + 1];
    switch (rstack[sp]->type) {
        case INT_TYPE:
            rstack[sp]->int_data = rstack[fpstack[fpsp] + rstack[sp]->int_data + 1]->int_data;
            break;
        case FLOAT_TYPE:
            rstack[sp]->float_data = rstack[fpstack[fpsp] + rstack[sp]->float_data + 1]->float_data;
            break;
        case CHAR_TYPE:
            rstack[sp]->char_data = rstack[fpstack[fpsp] + rstack[sp]->char_data + 1]->char_data;
            break;
        case SHORT_TYPE:
            rstack[sp]->short_data = rstack[fpstack[fpsp] + rstack[sp]->short_data + 1]->short_data;
            break;
    }
    pc++;
    debug();
}

void Interpreter::pushvf() {
    if (debug_flag){
        std::cout << "pushvf" <<std::endl;
    }
    //rstack[sp] = rstack[fpstack[fpsp] + rstack[sp] + 1];
    switch (rstack[sp]->type) {
        case INT_TYPE:
            rstack[sp]->int_data = rstack[fpstack[fpsp] + rstack[sp]->int_data + 1]->int_data;
            break;
        case FLOAT_TYPE:
            rstack[sp]->float_data = rstack[fpstack[fpsp] + rstack[sp]->float_data + 1]->float_data;
            break;
        case CHAR_TYPE:
            rstack[sp]->char_data = rstack[fpstack[fpsp] + rstack[sp]->char_data + 1]->char_data;
            break;
        case SHORT_TYPE:
            rstack[sp]->short_data = rstack[fpstack[fpsp] + rstack[sp]->short_data + 1]->short_data;
            break;
    }
    pc++;
}

void Interpreter::popm() {
    if (debug_flag){
        std::cout << "popm" <<std::endl;
    }
    //sp -= rstack[sp];
    switch (rstack[sp]->type) {
        case INT_TYPE:
            for (int i = 0; i <= rstack[sp]->int_data; i++) {
                rstack.pop_back();
            }
            sp -= rstack[sp]->int_data + 1;
            break;
        case FLOAT_TYPE:
            for (int i = 0; i <= int(rstack[sp]->float_data); i++) {
                rstack.pop_back();
            }
            sp -= int(rstack[sp]->float_data) + 1;
            break;
        case CHAR_TYPE:
            for (int i = 0; i <= rstack[sp]->char_data; i++) {
                rstack.pop_back();
            }
            sp -= rstack[sp]->char_data + 1;
            break;
        case SHORT_TYPE:
            for (int i = 0; i <= rstack[sp]->short_data; i++) {
                rstack.pop_back();
            }
            sp -= rstack[sp]->short_data + 1;
            break;
    }
    pc++;
    debug();
}

void Interpreter::popv() {
    if (debug_flag){
        std::cout << "popv" <<std::endl;
    }
   //rstack[fpstack[fpsp] + int(rstack[sp]) + 1] = rstack[sp-1];
    rstack[fpstack[fpsp] + rstack[sp]->int_data + 1]->int_data = rstack[sp-1]->int_data;
    sp -= 2;
    rstack.pop_back();
    rstack.pop_back();
    pc++;
    debug();
}

void Interpreter::popa() {
    if (debug_flag){
        std::cout << "popa" <<std::endl;
    }
    // Still need work, this assuming the top of rstack is an int



    int to_save = 0;
    switch (rstack[sp]->type) {
        case INT_TYPE:
            for(int i = 1; i < rstack[sp]->int_data; i++) {
                rstack[fpstack[fpsp] + i] = rstack[sp - rstack[sp]->int_data + (i - 1)];
            }
            to_save = rstack[sp]->int_data;
            break;
        case FLOAT_TYPE:
            for(int i = 1; i < rstack[sp]->float_data; i++) {
                rstack[fpstack[fpsp] + i] = rstack[sp - int(rstack[sp]->float_data) + (i - 1)];
            }
            to_save = int(rstack[sp]->float_data);
            break;
        case CHAR_TYPE:
            for(int i = 1; i < rstack[sp]->char_data; i++) {
                rstack[fpstack[fpsp] + i] = rstack[sp - rstack[sp]->char_data + (i - 1)];
            }
            to_save = rstack[sp]->char_data;
            break;
        case SHORT_TYPE:
            for(int i = 1; i < rstack[sp]->short_data; i++) {
                rstack[fpstack[fpsp] + i] = rstack[sp - rstack[sp]->short_data + (i - 1)];
            }
            to_save = rstack[sp]->short_data;
            break;
    }
    rstack.pop_back();
    sp--;

    rstack.erase(rstack.begin() + fpstack[fpsp] + 1, rstack.begin() + rstack.size() - to_save);

    sp = fpstack[fpsp]+rstack[sp]->int_data;
    pc++;
    debug();
}

void Interpreter::peekc() {
    //TODO: Implement this
    if (debug_flag){
        std::cout << "peekc" <<std::endl;
    }
 //   rstack[fpstack[fpsp] + rstack[sp-1]+1] = rstack[fpstack[fpsp]+rstack[sp]+1];
    pc++;
    rstack[fpstack[fpsp] + rstack[sp-1]->int_data+1]->char_data = rstack[fpstack[fpsp]+rstack[sp]->int_data+1]->char_data;
    rstack.pop_back();
    rstack.pop_back();
    sp -= 2;
    debug();
}

void Interpreter::peeks() {
    //TODO: Implement this
    if (debug_flag){
        std::cout << "peeks" <<std::endl;
    }
  //  rstack[fpstack[fpsp] + rstack[sp-1]+1] = rstack[fpstack[fpsp]+rstack[sp]+1];
    pc++;
    rstack[fpstack[fpsp] + rstack[sp-1]->int_data+1]->short_data = rstack[fpstack[fpsp]+rstack[sp]->int_data+1]->short_data;
    rstack.pop_back();
    rstack.pop_back();
    sp -= 2;
    debug();
}

void Interpreter::peeki() {
    if (debug_flag){
        std::cout << "peeki" <<std::endl;
    }
    pc++;
    rstack[fpstack[fpsp] + rstack[sp-1]->int_data+1]->int_data = rstack[fpstack[fpsp]+rstack[sp]->int_data+1]->int_data;
    rstack.pop_back();
    rstack.pop_back();
    sp -= 2;
    debug();
}

void Interpreter::peekf() {
    //TODO: Implement this
    if (debug_flag){
        std::cout << "peekf" <<std::endl;
    }
    pc++;
    rstack[fpstack[fpsp] + rstack[sp-1]->int_data+1]->float_data = rstack[fpstack[fpsp]+rstack[sp]->int_data+1]->float_data;
    rstack.pop_back();
    rstack.pop_back();
    sp -= 2;
    debug();
  //  rstack[fpstack[fpsp] + rstack[sp-1]+1] = rstack[fpstack[fpsp]+rstack[sp]+1];
}

void Interpreter::pokec() {
    //TODO: Implement this
    if (debug_flag){
        std::cout << "pokec" <<std::endl;
    }
    pc++;
    rstack[fpstack[fpsp] + rstack[sp]->int_data+1]->char_data = rstack[fpstack[fpsp]+rstack[sp - 1]->int_data+1]->char_data;
    rstack.pop_back();
    rstack.pop_back();
    sp -= 2;
    debug();
  //  rstack[fpstack[fpsp] + rstack[sp]+1] = rstack[fpstack[fpsp] + rstack[sp-1]+1];
}

void Interpreter::pokes() {
    //TODO: Implement this
    if (debug_flag){
        std::cout << "pokes" <<std::endl;
    }
    pc++;
    rstack[fpstack[fpsp] + rstack[sp]->int_data+1]->short_data = rstack[fpstack[fpsp]+rstack[sp - 1]->int_data+1]->short_data;
    rstack.pop_back();
    rstack.pop_back();
    sp -= 2;
    debug();
   // rstack[fpstack[fpsp] + rstack[sp]+1] = rstack[fpstack[fpsp] + rstack[sp-1]+1];
}

void Interpreter::pokei() {
    //TODO: Implement this
    if (debug_flag){
        std::cout << "pokei" <<std::endl;
    }
    pc++;
    rstack[fpstack[fpsp] + rstack[sp]->int_data+1]->int_data = rstack[fpstack[fpsp]+rstack[sp - 1]->int_data+1]->int_data;
    rstack.pop_back();
    rstack.pop_back();
    sp -= 2;
    debug();
  //  rstack[fpstack[fpsp] + rstack[sp]+1] = rstack[fpstack[fpsp] + rstack[sp-1]+1];
}

void Interpreter::pokef() {
    //TODO: Implement this
    if (debug_flag){
        std::cout << "pokef" <<std::endl;
    }
    pc++;
    rstack[fpstack[fpsp] + rstack[sp]->int_data+1]->float_data = rstack[fpstack[fpsp]+rstack[sp - 1]->int_data+1]->float_data;
    rstack.pop_back();
    rstack.pop_back();
    sp -= 2;
    debug();
  //  rstack[fpstack[fpsp] + rstack[sp]+1] = rstack[fpstack[fpsp] + rstack[sp-1]+1];
}

void Interpreter::swp() {
    if (debug_flag){
        std::cout << "swp" <<std::endl;
    }
    pc++;
    Data * tmp = rstack[sp-1];
    rstack[sp-1] = rstack[sp];
    rstack[sp] = tmp;
}

void Interpreter::add() {
    if (debug_flag){
        std::cout << "add" <<std::endl;
    }
//    rstack[sp-1] = rstack[sp-1] + rstack[sp];
    switch (rstack[sp]->type) {
        case INT_TYPE:
            rstack[sp - 1]->int_data = rstack[sp - 1]->int_data + rstack[sp]->int_data;
            break;
        case FLOAT_TYPE:
            rstack[sp - 1]->float_data = rstack[sp - 1]->float_data + rstack[sp]->float_data;
            break;
        case CHAR_TYPE:
            rstack[sp - 1]->char_data = rstack[sp - 1]->char_data + rstack[sp]->char_data;
            break;
        case SHORT_TYPE:
            rstack[sp - 1]->short_data = rstack[sp - 1]->short_data + rstack[sp]->short_data;
            break;
    }
    rstack.pop_back();
    sp--;
    pc++;
}

void Interpreter::sub() {
    if (debug_flag){
        std::cout << "sub" <<std::endl;
    }
//    rstack[sp-1] = rstack[sp-1] - rstack[sp];  
    switch (rstack[sp]->type) {
        case INT_TYPE:
            rstack[sp - 1]->int_data = rstack[sp - 1]->int_data - rstack[sp]->int_data;
            break;
        case FLOAT_TYPE:
            rstack[sp - 1]->float_data = rstack[sp - 1]->float_data - rstack[sp]->float_data;
            break;
        case CHAR_TYPE:
            rstack[sp - 1]->char_data = rstack[sp - 1]->char_data - rstack[sp]->char_data;
            break;
        case SHORT_TYPE:
            rstack[sp - 1]->short_data = rstack[sp - 1]->short_data - rstack[sp]->short_data;
            break;
    }
    rstack.pop_back();
    sp--;
    pc++;
}

void Interpreter::mul() {
    if (debug_flag){
        std::cout << "mul" <<std::endl;
    }
//    rstack[sp-1] = rstack[sp-1] * rstack[sp];
    switch (rstack[sp]->type) {
        case INT_TYPE:
            rstack[sp - 1]->int_data = rstack[sp - 1]->int_data * rstack[sp]->int_data;
            break;
        case FLOAT_TYPE:
            rstack[sp - 1]->float_data = rstack[sp - 1]->float_data * rstack[sp]->float_data;
            break;
        case CHAR_TYPE:
            rstack[sp - 1]->char_data = rstack[sp - 1]->char_data * rstack[sp]->char_data;
            break;
        case SHORT_TYPE:
            rstack[sp - 1]->short_data = rstack[sp - 1]->short_data * rstack[sp]->short_data;
            break;
    }
    rstack.pop_back();
    sp--;
    pc++;
}

void Interpreter::div() {
    if (debug_flag){
        std::cout << "div" <<std::endl;
    }
 //   rstack[sp-1] = rstack[sp-1] / rstack[sp];
    switch (rstack[sp]->type) {
        case INT_TYPE:
            rstack[sp - 1]->int_data = rstack[sp - 1]->int_data / rstack[sp]->int_data;
            break;
        case FLOAT_TYPE:
            rstack[sp - 1]->float_data = rstack[sp - 1]->float_data / rstack[sp]->float_data;
            break;
        case CHAR_TYPE:
            rstack[sp - 1]->char_data = rstack[sp - 1]->char_data / rstack[sp]->char_data;
            break;
        case SHORT_TYPE:
            rstack[sp - 1]->short_data = rstack[sp - 1]->short_data / rstack[sp]->short_data;
            break;
    }
    rstack.pop_back();
    sp--;
    pc++;
}

void Interpreter::printc() {
    if (debug_flag){
        std::cout << "printc" <<std::endl;
    }
    std::cout <<(int) rstack[sp--]->char_data << std::endl;
    rstack.pop_back();
    pc++;
}

void Interpreter::prints() {
    if (debug_flag){
        std::cout << "prints" <<std::endl;
    }
    pc++;
    std::cout <<rstack[sp--]->short_data<< std::endl;
    rstack.pop_back();
}

void Interpreter::printi() {
    if (debug_flag){
        std::cout << "printi" <<std::endl;
    }
    pc++;
    std::cout <<rstack[sp--]->int_data<< std::endl;
    rstack.pop_back();
}

void Interpreter::printf() {
    if (debug_flag){
        std::cout << "printf" <<std::endl;
    }
    pc++;
    std::cout <<rstack[sp--]->float_data<< std::endl;
    rstack.pop_back();
}

void Interpreter::halt() {
    if (debug_flag){
        std::cout << "halt" <<std::endl;
    }
    
    cout << endl << "Compile values:" << endl;
    cout << "PC: " << pc <<endl;
    cout << "sp: " << sp << endl;
    cout << "rstack: ";
    if (rstack.size() == 0) {
        cout << "empty";
    }
    for (int i = 0; i < rstack.size(); i++) {
        switch(rstack[i]->type){
        case INT_TYPE:
            cout << rstack[i]->int_data << " ";
            break;
        case FLOAT_TYPE:
            cout << rstack[i]->float_data << " ";
            break;
        case CHAR_TYPE:
            cout << rstack[i]->char_data << " ";
            break;
        case SHORT_TYPE:
            cout << rstack[i]->short_data << " ";
            break;
        }
    }
    cout <<endl;
    cout << "fpsp: " << fpsp << endl;
    cout << "fpstack: ";
    for (int i = 0; i < fpstack.size(); i++) {
        cout << fpstack[i] << " ";
    }
    if (fpstack.size() == 0) {
        cout << "empty" << endl;
    }
    cout <<endl;
    halt_flag = true;
}

void Interpreter::run_demo() {
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
void Interpreter::run() {
    while(!halt_flag && run_count != MAX_RUN) {
        switch(mem[pc]) {
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
            case 100://(100 || 01100100): //add
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
                cout <<"Unknown inst: " << (int) mem[pc] << endl;
                halt_flag = true;
                cout <<"Plz die a graceful death" << endl;
                return;
        }
        run_count++;
        if (run_count == MAX_RUN) {
            cout << "Max run reached" << endl;
        }
    }
}
