#pragma once

#include <iostream>
#include "Instruction2.hpp"

using namespace std;

class Label
{
  private:
    Instruction2 addresses[100];
    int count;

  public:
    Label(/* args */);
    int find(const char *) const;
    friend istream &operator>>(istream &is, Label &lbls);
};
