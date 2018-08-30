#pragma once

#include <iostream>
#include <fstream>
#include "Label.hpp"
#include "Word.hpp"
#include "Memory.hpp"
#include "Data.hpp"

using namespace std;

class Registers
{
  private:
    static const int zero_flag = 0x40;
    static const int sign_flag = 0x80;
    int registers[8];

  public:
    typedef enum
    {
        eax,
        ebp,
        esp,
        eip,
        edx,
        ebx,
        ecx,
        flags
    } Name;
    Registers(/* args */);

    int *address(char *, Memory &, const Label &);
    int get(Name n) const;
    bool get_sign_flag() const;
    bool get_zero_flag() const;

    void dump_to_file(string name);
    void load_from_file(string name);

    int string_to_reg_num(const char *str) const;
    int operator+=(int change);
    friend ostream &operator<<(ostream &os, const Registers &r);

    int *scaled_index_mode(char *operand, Memory &m) const;
    void set(Name n, int value);
    void set_flags(int value);
};
