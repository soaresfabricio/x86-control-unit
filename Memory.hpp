#pragma once

#include "Word.hpp"
#include "Instruction.hpp"

class Registers;
class Memory;

class List
{
  private:
    friend class Memory;
    Word *word;
    List *next;

  public:
    List(Word *w, List *l);
    ~List();
};

class Memory
{
  private:
    List *head;

  public:
    Memory(/* args */);
    ~Memory();
    const Instruction &fetch(Registers *r);
    Memory();
    ~Memory();
    Word &insert(Word *w);
    const Word &operator[](int a) const;
    Word &operator[](int a);
    friend istream &operator>>(istream &is, Memory &m);
};
