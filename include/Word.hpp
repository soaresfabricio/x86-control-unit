#pragma once


class Word
{
private:
public:
    int address;
    Word(int address);
    virtual ~Word();
    bool operator < (const Word &word) const;
};