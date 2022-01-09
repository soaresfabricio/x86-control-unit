#include "../include/Instruction.hpp"
#include <iomanip>
#include <cstring>

using namespace std;

Instruction::Instruction(int addr) : Word(addr), info(NULL){}

Instruction::~Instruction()
{
    if (info)
        delete[] info;
}

const char *Instruction::get_info() const
{
    return info;
}

void Instruction::operator=(const char *input_info)
{
    info = new char[strlen(input_info) + 1];
    strcpy(info, input_info);
}

ostream &operator<<(ostream &os, const Instruction &instruction)
{
    os << left << setw(30) << instruction.get_info();
    return os;
}