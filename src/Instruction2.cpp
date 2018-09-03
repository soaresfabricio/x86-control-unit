#include "../include/Instruction2.hpp"
#include <iostream>
#include <cstring>

Instruction2::Instruction2() : info(NULL){}

Instruction2::~Instruction2()
{
    if (info)
        delete[] info;
}

int Instruction2::get_address() const
{
    return address;
}

const char *Instruction2::get_info() const
{
    return info;
}

void Instruction2::set_address(int addr)
{
    address = addr;
}

void Instruction2::set_info(const char *input_info)
{
    info = new char[strlen(input_info) + 1];
    strcpy(info, input_info);
}