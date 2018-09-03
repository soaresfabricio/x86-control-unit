#include "../include/Word.hpp"

Word::Word(int address) : address(address) {}

Word::~Word() {}

bool Word::operator<(const Word &word) const
{
    if (address < word.address)
        return 1;
    else
        return 0;
}