#pragma once


class Instruction2
{
private:
    int address;
    char * info;
public:
    Instruction2(/* args */);
    ~Instruction2();
    int get_address() const;
    const char * get_info() const;
    void set_address(int a);
    void set_info(const char * information);
};
