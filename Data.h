#include <stdio.h>
#include <iostream>

using namespace std;
class Data {
public:
    Data();
    virtual ~Data();
    virtual void print_data() = 0;
};

class Int_Data : public Data {
private:
    int data;
public:
    Int_Data(int input);
    virtual ~Int_Data();
    virtual int get_data();
    virtual void print_data();

};


class Float_Data : public Data {
private:
    float data;
public:
    Float_Data(float input);
    virtual ~Float_Data();
    virtual float get_data();
    virtual void print_data();
};


class Short_Data : public Data {
private:
    short data;
public:
    Short_Data(short input);
    virtual ~Short_Data();
    virtual short get_data();
    virtual void print_data();
};