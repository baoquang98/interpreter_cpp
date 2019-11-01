#include <iostream>
#include <fstream>
#include <string.h>
#include "Interpreter.h"
using namespace std;
int main(int argc, char ** argv) {
    streampos size;
    unsigned char * memblock;
    if (argc != 3) {
        cout << "Mismatch arguments list, Usage: ./main [execution-flag] [input_file]" <<endl;
        cout << "-d for debug, -n for normal" << endl;
        return(EXIT_FAILURE);
    }
    fstream in_file(argv[2], ios::in | ios::binary | ios::ate);
    if (in_file.is_open()) {
        size = in_file.tellg();
        memblock = new unsigned char [size];
        in_file.seekg (0, ios::beg);
        in_file.read ((char *) memblock, size);
        in_file.close();
    
        /*for (int i = 0; i < size; i++) {
            cout << "Dec: " <<(int) memblock[i] << ", Hex: " << hex << (int) memblock[i] << dec << endl;
        }*/
        bool debug_flag;
        if (!strcmp(argv[1], "-d")) {
            debug_flag = true;
        } else if (!strcmp(argv[1], "-n")) {
            debug_flag = false;
        } else {
            cout << "Invalid flag" << endl;
            delete[] memblock;
            return(EXIT_FAILURE);
        }
        Interpreter * inter = new Interpreter(memblock, size, debug_flag); //keeping the size there because run_demo() method might still be useful
        inter->run();
        delete[] memblock;
        delete inter;
    } else cout << "Unable to open file";

    return(EXIT_SUCCESS);
}