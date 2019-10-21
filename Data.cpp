#include "Data.h"
#include <array>
#include <iostream>

Data::Data(){}
Data::~Data(){}
Int_Data::Int_Data(int input){
    data = input;
}
int Int_Data::get_data(){
    return (data);
}

void Int_Data::print_data(){
    std::cout << "int "<< data << " ";
}
Int_Data::~Int_Data(){}

Float_Data::Float_Data(float input){
    data = input;
}
float Float_Data::get_data(){
    return (data);
}
Float_Data::~Float_Data(){}

void Float_Data::print_data(){
    std::cout << "float " << data << " ";
}


Short_Data::Short_Data(short input){
    data = input;
}
short Short_Data::get_data(){
    return (data);
}

void Short_Data::print_data(){
    std::cout <<"short " <<data << " ";
}
Short_Data::~Short_Data(){}