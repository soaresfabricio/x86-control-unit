#pragma once


class Word
{
private:
    int address;
public:
    Word(/* args */);
    virtual ~Word();
    bool operator < (const Word &word) const;
};

Word::Word(/* args */)
{
}

Word::~Word()
{
}
