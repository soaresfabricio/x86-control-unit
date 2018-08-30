#include <iostream>
#include <cstdlib>
#include "Decoder.hpp"
#include "Instruction.hpp"
#include "Registers.hpp"
#include "Data.hpp"
#include "memory"

using namespace std;

void Decoder::addl(Registers *ops)
{
    *op2 = *op1 + *op2;
    ops->set_flags(*op2);
}

void Decoder::andl(Registers *ops)
{
    *op2 = *op1 & *op2;
    ops->set_flags(*op2);
}

void Decoder::call(Registers *ops, Memory &mem) const
{
    Data &d = dynamic_cast<Data &>(mem[ *ops += -4]);
    d = ops->get(Registers::eip);
}