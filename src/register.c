#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "../include/utils.h"
#include "../include/register.h"

const char* registers[] = {
    "A0",
    "A1",
    "A2",
    "A3",

    "\0"
};

int isRegister(char* str){

    int i = 0;
    char reg[4];

    if(strlen(str) > 4)
        return 0;

    strcpy(reg, str);
    toUpper(reg);

    while(registers[i][0] != '\0'){

        if(strcmp(registers[i], reg) == 0){
            return 1;
        }
        i++;
    }
    return 0;
}

uint16_t numRegister(char* str){
    int i = 0, ret = -1;
    char input[10];
    strcpy(input, str);
    toUpper(input);

    while(registers[i][0] != '\0'){

        if(strcmp(registers[i], input) == 0){
            ret = i;
        }
        i++;
    }
    return ret;
}

BOOL isLiteral(char* str){

    int i;
    char inpt[20];
    BOOL ret = TRUE;

    for(i = 0; str[i] != '\0'; i++){

        if(str[i] == '#' && i == 0){
            break;
        }

        if(str[i] == ','){
            break;
        }

        else if(!isDigit(str[i])){
            return FALSE;
        }

        if(i == 20){
            return FALSE;
        }
    }

    return TRUE;
}

BOOL isOperator(char* str){ // <--

    BOOL isNum = TRUE;
    int i;

    for(i = 0; str[i] != '\0'; i++){ // Verifica se é um inteiro
        if(!isDigit(str[i])){
            isNum = FALSE;
        }
    }
}

void printRegisters(uint8_t registerFile[]){
	
	for(int i = 0; registers[i][0] != '\0'; i++){
		//printf("(%p)", &registerFile[i]);
		printf("\t%s: ", registers[i]);
		printf("%d\n", registerFile[i]);
	}
}