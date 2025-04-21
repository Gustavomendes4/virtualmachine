#ifndef INSTRUCTION_H_DEFINED
#define INSTRUCTION_H_DEFINED

#include <stdio.h>

typedef enum InstructionCode{
    ADD, //0000
    SUB, //0001
    MUL, //0010
    DIV, //0011
    MV,
    ST,
    JMP,
    JEQ,
    JGT,
    JLT,
    W,
    R,
    STP,
    NOP,

    _NOT_A_INSTRUCT
}InstructionCode;

int isInstruction(char* str);

InstructionCode instructionCode(char* str);

void instructionBin(char* str);

#endif