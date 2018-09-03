#pragma once

#include "Instruction.hpp"
#include "Registers.hpp"
#include "Label.hpp"

class Decoder
{
  private:
    char opcode[20];
    int *op1;
    int *op2;

    void addl(Registers *);
    void andl(Registers *);
    void call(Registers *, Memory &m) const;
    void cmpl(Registers *) const;
    void incl(Registers *);
    void jg(Registers *) const;
    void jle(Registers *) const;
    void jmp(Registers *) const;
    void leal(const Instruction &i, const Registers *);
    void leave(Registers *, const Memory &m) const;
    void movl();
    void pushl(Registers *, Memory &m) const;
    void ret(Registers *, const Memory &m) const;
    void sall(Registers *);
    void subl(Registers *);
    void decl(Registers *) const;
    void imull(Registers *);

  public:
    void execute(const Instruction & n, Registers *, Memory & m);
    void parse(const Instruction & i, Registers *, Memory & m, const Label & l);
};
