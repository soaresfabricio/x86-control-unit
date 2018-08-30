#pragma once

#include "Word.hpp"

class Data: public Word
{
private:
    int num;
public:
    Data(int address);
    int & get();
    const int & get() const;
    int operator = (int value);
    ~Data();
};
