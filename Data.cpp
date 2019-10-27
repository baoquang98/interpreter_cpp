#include "Data.h"
#include <array>
#include <iostream>

Data::Data(int input){int_data = input; type = INT_TYPE;}
Data::Data(float input){float_data = input; type = FLOAT_TYPE;}
Data::Data(char input){char_data = input; type = CHAR_TYPE;}
Data::Data(short input){short_data = input; type = SHORT_TYPE;}
Data::~Data(){}
