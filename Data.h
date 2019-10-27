#include <stdio.h>
#include <iostream>
#define INT_TYPE 1
#define FLOAT_TYPE 2
#define SHORT_TYPE 3
#define CHAR_TYPE 4
using namespace std;
class Data {
public:
    int type;
    char char_data;
    int int_data;
    float float_data;
    short short_data;
    Data(int input);
    Data(float input);
    Data(char input);
    Data(short input);
    virtual ~Data();
};
