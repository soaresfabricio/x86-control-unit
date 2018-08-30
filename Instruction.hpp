#pragma once

#include <iostream>
#include "Word.hpp"

using namespace std;

class Instruction
{
private:
    char * info;
public:
    Instruction(/* args */);
    ~Instruction();
    const char * get_info() const;
    void set_info(const char * i);
    void operator=(const char * i);
    friend ostream& operator << (ostream & os, const Instruction& i);
};

Instruction::Instruction(/* args */)
{
}

Instruction::~Instruction()
{
}
