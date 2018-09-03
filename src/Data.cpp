#include "../include/Data.hpp"

Data::Data(int address) : Word(address) {}

int &Data::get()
{
  return num;
}

const int &Data::get() const
{
  return num;
}

int Data::operator=(int value)
{
  num = value;
  return value;
}