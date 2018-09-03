#include <cstdlib>
#include <iostream>
#include <cstring>
#include "../include/Memory.hpp"
#include "../include/Word.hpp"
#include "../include/Data.hpp"
#include "../include/Registers.hpp"

using namespace std;

Memory::Memory() : head(NULL){}

/** TODO: SAVE TO FILE */
Memory::~Memory()
{
    List *ptr;
    for (ptr = head; ptr; ptr = head)
    {
        head = ptr->next;
        delete ptr;
    }
}

List::List(Word* w, List *listNode)
{
  word = w;
  next = listNode;
} 

List::~List()
{
  delete word; 
}

Word &Memory::insert(Word *word)
{
    List *ptr, *pre = NULL;

    for (ptr = head; ptr && *(ptr->word) < *word; ptr = ptr->next)
        pre = ptr;

    if (pre)
    {
        pre->next = new List(word, ptr);
        return *(pre->next->word);
    }

    head = new List(word, ptr);
    return *(head->word);
}

// const [] operation
const Word &Memory::operator[](int addr) const
{
    List *ptr;
    Word temp(addr);

    for (ptr = head; ptr && *(ptr->word) < temp; ptr = ptr->next);

    if (!ptr || temp < *(ptr->word))
    {
        cout << "Segmentation fault at address: " << addr << endl;
        exit(1);
    }

    return *(ptr->word);
} 

// normal [] operation
Word& Memory::operator[] (int addres)
{
  List *ptr;
  Word temp(addres); 
  
  for (ptr = head; ptr && *(ptr->word) < temp; ptr = ptr->next);
  
  if (!ptr || temp < *(ptr->word))
  {
    Data *data = new Data(addres);
    return insert(data);
  } 
  
  return *(ptr->word);
}

/** Fetches the instruction at the position given by the EIP register
 *  and sets the register to the following position. */
const Instruction& Memory::fetch(Registers *regs)
{
  int pos = regs->get(Registers::eip);
  const Instruction& instruction = dynamic_cast<Instruction&>((*this)[pos]);
  regs->set(Registers::eip, regs->get(Registers::eip) + 4);
  return instruction;
} // fetch()

istream &operator>>(istream &is, Memory &mem)
{
    char line[256], *ptr;
    int address = 100;
    Instruction *inst;

    // Seeking through the file
    while (is.getline(line, 256))
    {
        // Seeks for horizontal tabs and replaces them with space characters
        for (ptr = strchr(line, '\t'); ptr; ptr = strchr(line, '\t'))
            *ptr = ' ';

        // Skipping occasional spaces
        for (ptr = line; *ptr == ' '; ptr++)
            ;

        // Did it hit a label/directive?
        if (*ptr != '.' && *ptr != '_' && !strstr(line, "main:") && !strchr(line, ':'))
        {
            inst = new Instruction(address);
            address += 4;
            *inst = ptr;
            mem.insert(inst);
        } 
    } 

    return is;
}
