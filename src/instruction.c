#include <stdio.h>
#include <string.h>

#include "../include/utils.h"
#include "../include/instruction.h"

const char* instructions[] = {
    "add", //ADD,
    "sub", //SUB,
    "mul", //MUL,
    "div", //DIV,
    "mv", //MV,
    "st", //ST,
    "jmp", //JMP,
    "jeq", //JEQ,
    "jgt", //JGT,
    "jlt", //JLT,
    "w", //W,
    "r", //R,
    "stp", //STP,
    "nop", //NOP,
     
    "\0" // last
};

const char* binaryInstruction[] = {
    //Instruções de uso geral
        "0000.xxxx",     //"nop",
        "1111.xxxx",     //"hlt",

    //Instruções de Controle de Fluxo    
        "0100.xxxx",     //"jmp",
        "0011.0000",     //"br",
        "0011.0001",     //"bne",
        "0011.0010",     //"beq",
        "0011.0011",     //"bpl",
        "0011.0100",     //"bmi",
        "0011.0101",     //"bvc",
        "0011.0110",     //"bvs",
        "0011.0111",     //"bcc",
        "0011.1000",     //"bcs",
        "0011.1001",     //"bge",
        "0011.1010",     //"blt",
        "0011.1011",     //"bgt",
        "0011.1100",     //"ble",
        "0011.1101",     //"bhi",
        "0011.1110",     //"bls",
        "0110.xxxx",     //"jsr",
        "0111.xxxx",     //"rts",

    //Instruções com 1 operando
        "1000.0000",     //"clr",
        "1000.0001",     //"not",
        "1000.0010",     //"inc",
        "1000.0011",     //"dec",
        "1000.0100",     //"neg",
        "1000.0101",     //"tst",
        "1000.0110",     //"ror",
        "1000.0111",     //"rol",
        "1000.1000",     //"asr",
        "1000.1001",     //"asl",
        "1000.1010",     //"adc",
        "1000.1011",     //"sbc",
    //Instruções com 2 operando
        "1001.xxxx",     //"mov",
        "1010.xxxx",     //"add",
        "1011.xxxx",     //"sub",
        "1100.xxxx",     //"cmp",
        "1101.xxxx",     //"and",
        "1110.xxxx",     //"or",

    //Instruções especiais
        "0001.xxxx",     //"ccc",
        "0010.xxxx",     //"scc",
        "0101.xxxx",     //"sob",
     
        "\0"
};

int isInstruction(char* str){

    char inst[30];

    strcpy(inst, str);
    toLower(inst);

    int i = 0;
    while(instructions[i][0] != '\0'){

        if(strcmp(instructions[i], inst) == 0){
            return 1;
        }
        i++;
    }

    return 0;
}

InstructionCode instructionCode(char* str){

    char inst[30];
    
    strcpy(inst, str);
    toLower(inst);
    
    InstructionCode i = 0;
    while(instructions[i][0] != '\0'){
    
        if(strcmp(instructions[i], inst) == 0){
            return i;
        }
        i++;
    }
    
    return -1;
}

void instructionBin(char* str){
    InstructionCode code = instructionCode(str);
    if(code < 0 || code >= _NOT_A_INSTRUCT){
        str[0] = '\0';
        return;
    }
    strcpy(str, binaryInstruction[code]);
}
