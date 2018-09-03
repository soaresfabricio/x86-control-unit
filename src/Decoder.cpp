#include <cstring>
#include <iostream>
#include <cstdlib>
#include "../include/Decoder.hpp"
#include "../include/Instruction.hpp"
#include "../include/Registers.hpp"
#include "../include/Data.hpp"
#include "memory"

using namespace std;

const char *opcodes[] = {"addl", "andl", "leave", "movl", "pushl", "ret",
                         "subl", "cmpl", "incl", "jg", "jle", "jmp", "leal", "call", "sall",
                         "decl", "imull", "nop", "jl", "jge"};

enum OpcodeNum
{
    ADDL,
    ANDL,
    LEAVE,
    MOVL,
    PUSHL,
    RET,
    SUBL,
    CMPL,
    INCL,
    JG,
    JLE,
    JMP,
    LEAL,
    CALL,
    SALL,
    DECL,
    IMULL,
    NOP,
    JL,
    JGE
};

void Decoder::parse(const Instruction &inst, Registers *regs, Memory &mem, const Label &lbls)
{
    char *ptr, info[1000];

    strcpy(info, inst.get_info());

    strcpy(opcode, strtok(info, " "));

    ptr = strtok(NULL, " ");

    if (ptr)
    {
        op1 = regs->address(ptr, mem, lbls);
        ptr = strtok(NULL, " ");
        if (ptr)
            op2 = regs->address(ptr, mem, lbls);
    }
}

void Decoder::addl(Registers *regs)
{
    *op2 = *op1 + *op2;
    regs->set_flags(*op2);
}

void Decoder::andl(Registers *regs)
{
    *op2 = *op1 & *op2;
    regs->set_flags(*op2);
}


/** 
 * The LEAVE instruction copies the frame pointer (in the EBP register) 
 * into the stack pointer register (ESP), which releases the stack space 
 * allocated to the stack frame.
*/
void Decoder::leave(Registers * regs, const Memory &mem) const {
    regs->set(Registers::esp, regs->get(Registers::ebp));
    const Data &data = dynamic_cast <const Data&> (mem[regs->get(Registers::esp)]);
    regs->set(Registers::ebp, data.get());
    *regs += 4;
}

/** Copies the second operand (source operand) to the first operand (destination operand). */
void Decoder::movl()
{
    *op2 = *op1;
}

/** Decrements the stack pointer and then stores the source operand on the top of the stack.  */
void Decoder::pushl(Registers *regs, Memory &mem) const
{
    Data &data = dynamic_cast <Data&>(mem[*regs += -4]);
    data = *op1;
}

/** Transfers program control to a return address located on the top of the stack. */
void Decoder::ret(Registers *regs, const Memory &mem) const
{
    const Data &data = dynamic_cast <const Data &>(mem[regs->get(Registers::esp)]);
    regs->set(Registers::eip, data.get());
    *regs += 4;
}

/** Subtracts the second operand (source operand) from the first operand
 *  (destination operand) and stores the result in the destination operand. 
 *  The SF flag indicates the sign of the signed result. */
void Decoder::subl(Registers *regs)
{
    *op2 = *op2 - *op1;
    regs->set_flags(*op2);
}

/** Compares the first source operand with the second source operand and sets the status 
 *  flags according to the results.  */
void Decoder::cmpl(Registers *regs) const
{
  regs->set_flags(*op2 - *op1);
} 

/** Adds 1 to the destination operand, while preserving the state of the CF flag. */
void Decoder::incl(Registers *regs)
{
  regs->set_flags(++(*op1));
} 

/** Performs a signed comparison jump after a cmp if the destination operand is 
 * greater than the source operand */
void Decoder::jg(Registers *regs) const
{
    if (!regs->get_sign_flag() && !regs->get_zero_flag())
        regs->set(Registers::eip, *op1);
}

void Decoder::jle(Registers *regs) const
{
    if (regs->get_sign_flag() || regs->get_zero_flag())
        regs->set(Registers::eip, *op1);
}


/** Transfers program control to a different point in the instruction stream 
 * without recording return information. The destination (target) operand 
 * specifies the address of the instruction being jumped to. */
void Decoder::jmp(Registers *regs) const
{
    regs->set(Registers::eip, *op1);
}


/** Load Effective Address instruction. Performs an address calculation.
 * It doesn't know if it is an address or not, it just computes a value. 
 * movl, on the other hand, will try to read a value from the address, 
 * and will notice if it is not valid (inaccessible)
 * */
void Decoder::leal(const Instruction &inst, const Registers *regs)
{
    char *ptr, info[1000];
    Registers::Name reg;

    strcpy(info, inst.get_info());
    strtok(info, " "); 
    ptr = strtok(NULL, " ");

    reg = (Registers::Name) regs->string_to_reg_num(ptr);
    *op2 = atoi(ptr) + regs->get(reg);
}

/** Pushes the current code location onto the stack in memory and then performs
 * an unconditional jump to the code location indicated by the label operand. 
 * Unlike the simple jump instructions, the call instruction saves the location 
 * to return to when the subroutine completes. */
void Decoder::call(Registers *regs, Memory &mem) const
{
    Data &data = dynamic_cast<Data &>(mem[ *regs += -4]);
    data = regs->get(Registers::eip);
    regs->set(Registers::eip, *op1);
}

/**Left shifts (multiplies) a byte, word, or long value for a count specified 
 * by an immediate value */
void Decoder::sall(Registers *regs)
{
    *op2 <<= *op1;
    regs->set_flags(*op2);
}


/** The dec instruction decrements the contents of its operand by one. */
void Decoder::decl(Registers *regs) const
{
    regs->set_flags(--*op1);
}

/**Multiplies its two operands together and stores the result in the second operand. 
 * The result (i.e. second) operand must be a register. */
void Decoder::imull(Registers *regs)
{
    *op2 = *op1 * *op2;
    regs->set_flags(*op2);
}

void Decoder::execute(const Instruction &inst, Registers *regs, Memory &mem)
{
    int opcode_num;

    for (opcode_num = ADDL; strcmp(opcode, opcodes[opcode_num]) != 0 || opcode_num > JGE; ++opcode_num)
        ;

    switch(opcode_num){
        case ADDL:  addl(regs); break;
        case ANDL:  andl(regs); break;
        case LEAVE: leave(regs, mem); break;
        case MOVL:  movl(); break;
        case PUSHL: pushl(regs,mem); break;
        case RET:   ret(regs,mem); break;
        case SUBL:  subl(regs); break;
        case CMPL:  cmpl(regs); break;
        case INCL:  incl(regs); break;
        case JG:    jg(regs); break;
        case JLE:   jle(regs); break;
        case JMP:   jmp(regs); break;
        case LEAL:  leal(inst, regs); break;
        case CALL:  call(regs, mem); break;
        case SALL:  sall(regs); break;
        case DECL:  decl(regs); break;
        case IMULL: imull(regs); break;
        case NOP:   break;
        case JL:    jle(regs); break;
        case JGE:   jg(regs); break;
        default: cout << "opcode not recognized or invalid.\n";
    }
}
