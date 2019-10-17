#include <iostream>
#include <fstream>
#include "Interpreter.h"
using namespace std;
int main(int argc, char ** argv) {
    streampos size;
    unsigned char * memblock;
    fstream in_file("interpreter_input.smp", ios::in | ios::binary | ios::ate);
    if (in_file.is_open()) {
        size = in_file.tellg();
        memblock = new unsigned char [size];
        in_file.seekg (0, ios::beg);
        in_file.read ((char *) memblock, size);
        in_file.close();
    
        /*for (int i = 0; i < size; i++) {
            cout << "Dec: " <<(int) memblock[i] << ", Hex: " << hex << (int) memblock[i] << dec << endl;
        }*/
        Interpreter * inter = new Interpreter(memblock, size); // temp solution for c++ being picky with array size
        inter->run();
        delete[] memblock;
    } else cout << "Unable to open file";

    return(EXIT_SUCCESS);
}