#pragma once

#include "Word.hpp"

class Data: public Word
{
private:
    int num;
public:
    Data(int);
    int & get();
    const int & get() const;
    int operator = (int);
};
