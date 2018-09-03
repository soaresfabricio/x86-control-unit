#pragma once

#include <iostream>
#include "Word.hpp"

using namespace std;

class Instruction: public Word
{
  private:
    char *info;
    
  public:
    Instruction(int);
    ~Instruction();
    const char *get_info() const;
    void set_info(const char *i);
    void operator=(const char *i);
    friend ostream &operator<<(ostream &os, const Instruction &i);
};
