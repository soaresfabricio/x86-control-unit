#include <cstring>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "../include/Registers.hpp"

using namespace std;

// Defaulting value
Registers::Registers()
{
    registers[esp] = 1000; // stack pointer
    registers[ebp] = 996; // stack frame
    registers[eip] = 100; // extended instruction pointer
    registers[eax] = 0;
    registers[edx] = 0;
    registers[ebx] = 0;
    registers[ecx] = 0;
    registers[flags] = 0xC0;
}

// Fetches the value for a certain op
int *Registers::address(char *op, Memory &mem, const Label &l)
{
    if(op == NULL) return NULL;

    static int value;

    // Immediate Mode (memory is not accessed) - operand is part of the instruction.
    // For example, a constant encoded in the instruction.
    if (op[0] == '$')
    {
        value = atoi(&op[1]);
        return &value;
    }

    // Scaled mode: These modes let you multiply the index register in the
    // addressing mode by one, two, four, or eight.
    // segment:displacement(base register, index register, scale factor)
    if (strchr(op, ',') && strchr(op, ',') != strrchr(op, ','))
        return scaled_index_mode(op, mem);
    
    int reg_num = string_to_reg_num(op);
    char * ptr = strchr(op, '(');
    int index = 0;

    // Indirect addressing: transfer control to the instruction whose address is in the specified register.
    if (ptr)
    {
        *ptr = '\0';
        index = atoi(op);
        Data &data = dynamic_cast<Data &>(mem[registers[reg_num] + index]);
        return &(data.get());
    }

    // Direct mode
    if(op[0] == '%') return &(registers[reg_num]); 

    // Label
    else{
        value = l.find(op);
        return & value;
    }
}

// segment:displacement(base register, index register, scale factor)
int *Registers::scaled_index_mode(char *op, Memory &mem) const
{
    int offset, base, index, factor;
    char *ptr = op, *ptr2;

    // Replacing the first parathensis with the null character
    while (*ptr != '(')
        ptr++;
    *ptr = '\0';

    // Storing string it as the displacement
    offset = atoi(op);

    // Backing up the pointer
    ptr2 = ++ptr;

    // Replacing the first comma with the null character
    while (*ptr != ',')
        ptr++;
    *ptr = '\0';

    // Storing it as the base value
    base = string_to_reg_num(ptr2);

    // Backing up the pointer
    ptr2 = ++ptr;

    // Replacing the second comma with the null character
    while (*ptr != ',')
        ptr++;
    *ptr = '\0';

    // Storing it as the index value
    index = string_to_reg_num(ptr2);

    // Storing the scale factor
    factor = atoi(++ptr);

    Data &data = dynamic_cast<Data &>(mem[registers[base] + factor * registers[index] + offset]);
    return &(data.get());
}

int Registers::string_to_reg_num(const char *str) const
{
    char names[7][7] = {"eax", "ebp", "esp", "eip", "edx", "ebx", "ecx"};

    int i;
    for (i = eax; i <= ecx; i++)
    {
        if (strstr(str, names[i]))
            break;
    }

    return i;
}

int Registers::get(Name name) const
{
    if (name < eax || name > ecx)
        return 0;

    return registers[name];
}

void Registers::set(Name name, int value)
{
    // Bound checking
    if (name >= eax && name <= ecx)
        registers[name] = value;
}

void Registers::set_flags(int x)
{
    if (!x)
        registers[flags] |= zero_flag; // Setting
    else
        registers[flags] &= ~zero_flag; // Resetting

    if (x < 0)
        registers[flags] |= sign_flag; // Setting
    else
        registers[flags] &= ~sign_flag; // Resetting
}

bool Registers::get_zero_flag() const{
    return registers[flags] & zero_flag;
}

bool Registers::get_sign_flag() const{
    return registers[flags] & sign_flag;
}

int Registers::operator+= (int x){
    registers[esp] += x;
    return registers[esp];
}

ostream& operator<< (ostream &os, const Registers &r)
{
  os << " eip: " << right << setw(3) << r.registers[Registers::eip] 
    << " eax: " << setw(3) << r.registers[Registers::eax] 
    << " ebp: " << setw(3) << r.registers[Registers::ebp] 
    << " esp: " << setw(3) << r.registers[Registers::esp] 
    << " edx: " << setw(3) << r.registers[Registers::edx] 
    << " ebx: " << setw(3) << r.registers[Registers::ebx] 
    << " ecx: " << setw(3) << r.registers[Registers::ecx] 
    << " flags: " << setw(3) << r.registers[Registers::flags] << endl;
  
  return os;
}

void Registers::load_from_file(string file_name)
{
  ifstream input(file_name);

  if (input.is_open())
  {
    int value = 0;
    int i = 0;
    while (input >> value)
    {
      registers[i] = value;
      i++;
    }
    
    registers[esp] = 1000;
    registers[ebp] = 996;
    registers[eip] = 100;

    cout << "Registers loaded from " + file_name << endl;
  }
  else
  {
    cout << "There was a problem opening the file: " + file_name << endl;
  }
}


void Registers::dump_to_file(string file_name)
{
  ofstream output(file_name);

  if (output.is_open())
  {
    cout << "Saving registers to " + file_name;

    for (auto r : registers)
    {
      output << r << endl;
    }

    cout << "... DONE" << endl;
  } else {
      cout << "There was a problem opening the file: " + file_name << endl;
  }
}