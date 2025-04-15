#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

//#include "../include/utils.h"
#include "../include/file.h"
#include "../include/error.h"
#include "../include/label.h"
#include "../include/instruction.h"
#include "../include/register.h"

#define MEMORY_LEN 320

uint16_t a0=0, a1=1, a2=2, a3=3, Pc = 0;
//uint16_t* registerList[4] = {&a0, &a1, &a2, &a3};
uint16_t registerFile[4] = {0, 1, 2, 3};

uint8_t memory[MEMORY_LEN];

int process(uint8_t* memory);
InstructionCode decodOperation(uint8_t byte);
void loader(FILE* file);
void printMemory();
void printRegisters();

FILE* processInputFile(int argc, char* argv[]){
	char* path;
	FILE *file;

	if(argc == 1)
		exit(error(ERR_NO_ARGUMENT, "", 0));
	else
		path = argv[1];


	char* ext = getFileExtension(path);
	if(!extensionAccepted(ext)){
		exit(error(ERR_INVALID_EXTENSION, ext, 0));
	}

	if((file = fopen(path, "rb")) == NULL){
		exit(error(ERR_FILE_NOT_FOUND, path, 0));
	}

	return file;
}

int main(int argc, char* argv[]){
	FILE *file = processInputFile(argc, argv);
	loader(file);
	fclose(file);
	//printMemory(memory);
	process(memory);
	return 1;
}

int process(uint8_t* memor){

	int stp = 1;
	uint16_t *ra, *rb, *rc;
	uint16_t mem1, mem2;

	while(stp && Pc < MEMORY_LEN){
		ra = &registerFile[(memory[Pc] & 12) >> 2];
		rb = &registerFile[memory[Pc] & 3];
		rc = &registerFile[(memory[Pc+1] & 192) >> 6];

		mem1 = memory[Pc] & 1;
		mem1 = (mem1 << 8) + memory[Pc+1];
		mem2 = memory[Pc+1] << 1;

		switch(decodOperation(memory[Pc])){
			case  ADD:	(*ra = *rb + *rc);	break;
			case  SUB:	(*ra = *rb - *rc);	break;
			case  MUL:	(*ra = *rb * *rc);	break;
			case  DIV:	(*ra = *rb / *rc);	break;

			case  MV :	(*ra = memory[mem1]);	break;
			case  ST :	(memory[mem1] = *ra);	break;

			case  JMP:	(Pc = mem1);	break;
			case  JEQ:	Pc = (*ra == *rb)? mem2 : Pc;	break;
			case  JGT:	Pc = (*ra > *rb) ? mem2 : Pc;	break;
			case  JLT:	Pc = (*ra < *rb) ? mem2 : Pc;	break;

			case  W  :	(putchar(' '));	break;//
			case  R  :	(putchar(' '));	break;//
			case  STP: stp = 0;	break;
		}
		Pc += 2;
	}

	printRegisters();
	return SUCCESS;
}

void loader(FILE* file){
	
	int i = 0;
	uint8_t byte;

	fread(&Pc, sizeof(Pc), 1, file);	// Lê o primeiro byte, que é o valor inicial do PC

	while(fread(&byte, sizeof(byte), 1, file)){

		if(i == MEMORY_LEN){
			exit(error(ERR_PROGRAM_LONGER, "", 0));
		}
		memory[i++] = byte;
	}
}

void printMemory(){
	int i;
	uint8_t byte;

	printf("\n\t ________________\n\t|     MEMORY     |\n\t|________________|\n\t");
	for(i = 0; i < MEMORY_LEN; i++){
		printf("|  %03x  |  %04d  |\n\t", i, memory[i]);
	}
	printf("|_______|________|\n\n");
}

void printRegisters(){
	
	for(int i = 0; i < 4; i++){
		//printf("(%p)", &registerFile[i]);
		printf("\ta%d: ", i);
		printf("%d\n", registerFile[i]);
	}
}

InstructionCode decodOperation(uint8_t byte){
	uint8_t ch = byte & 0b11110000;
	ch = ch >> 4;
	return ch;
}
