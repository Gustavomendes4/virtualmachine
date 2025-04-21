#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/utils.h"
#include "../include/file.h"
#include "../include/error.h"
#include "../include/label.h"
#include "../include/instruction.h"
#include "../include/register.h"

#define MEMORY_LEN 320

void printAllWord(FILE* file);
void printMemory(uint8_t memory[]);
void pushMemory(uint8_t memory[], uint16_t instruction, uint16_t PC);
void process(FILE* file, uint8_t memory[], uint16_t* PC);
FILE* processInputFile(int argc, char* argv[]);
FILE* processOutputFile(int argc, char* argv[]);
ErrorCode loadOutFile(FILE* file, uint8_t* memory);
void variablesDeclaration(FILE* file, uint8_t memory[], uint16_t* PC, char* goal);

uint16_t R_instruction(InstructionCode code, FILE* file);
uint16_t M_instruction(InstructionCode code, FILE* file, Label* labels);
uint16_t J_instruction(InstructionCode code, FILE* file, Label* labels);
uint16_t O_instruction(InstructionCode code, FILE* file, Label* labels);


int line = 1;

int main(int argc, char* argv[]){

	uint16_t Pc;
	uint8_t memory[MEMORY_LEN];
	
	for(int i = 0; i < MEMORY_LEN; i++) memory[i] = 0;

	FILE *fileIn  = processInputFile(argc, argv);
	process(fileIn, memory, &Pc);
	//printMemory(memory);

	if(errorListIsEmpty()){
		FILE *fileOut = processOutputFile(argc, argv);
		loadOutFile(fileOut, memory);
		return SUCCESS;
	}

	printErrorList();
	return ERR_UNKNOWN;
}

void process(FILE* file, uint8_t memory[], uint16_t* Pc){

	//printAllWord(file);
	
	InstructionCode code;
	uint16_t instruction;
	char word[30];
	
	Label* labels = createLabelList(file);				printLabelList(labels);
	variablesDeclaration(file, memory, Pc, word);
	pushMemory(memory, (*Pc) - 2, 0);

	while(!feof(file)){

		if(isLabelDeclaration(labels, word)){
			line += getFileWord2(file, word);
			continue;
		}

		code = instructionCode(word);
		switch(code){

			case ADD: case SUB: case MUL: case DIV:{
				instruction = R_instruction(code, file);
			}break;

			case MV : case ST:{
				instruction = M_instruction(code, file, labels);
			}break;

			case JMP: case JEQ: case JGT: case JLT:{
				instruction = J_instruction(code, file, labels);
			}break;

			case W  : case R  :{
				instruction = O_instruction(code, file, labels);
			}break;

			case STP:{instruction = 49152;}break;
			case NOP:{instruction = 53248;}break;

			default:
				error(ERR_NOT_A_INSTRUCTION, word, line);
		}

		//printf("\n%d", instruction);
		pushMemory(memory, instruction, *Pc);
		*Pc += 2;

		line += getFileWord2(file, word);
	}
}

void printAllWord(FILE* file){

	char word[30];

	while(!feof(file)){
		line += getFileWord2(file, word);
		printf("\n\t%-10s", word);

	}
	rewind(file);
}

FILE* processInputFile(int argc, char* argv[]){

	FILE *file;
	char __input[_MAX_PATH];
	char* path = __input;

	if(argc == 1){
		exit(error(ERR_NO_ARGUMENT, "", 0));
	}
	else{
		path = argv[1];
	}

	char* ext = getFileExtension(path);
	if(!extensionAccepted(ext, 1)){
		exit(error(ERR_INVALID_EXTENSION, ext, 0));
	}

	if((file = fopen(path, "rw")) == NULL){
		exit(error(ERR_FILE_NOT_FOUND, path, 0));
	}

	return file;
}

FILE* processOutputFile(int argc, char* argv[]){

	FILE *fileOut;
	char __output[_MAX_PATH];
	char* pathOut = __output;
	char* outExt;

	if(argc < 3){
		outputFileName(pathOut, argv[1]);
	}
	else{
		strcpy(pathOut, argv[2]);
	}

	outExt = getFileExtension(pathOut);
	if(outExt == NULL){
		strcat(pathOut, OUTPUT_EXTENSION);
	}	
	else if(strcmp(outExt, OUTPUT_EXTENSION) != 0){
		exit(error(ERR_INVALID_OUT_EXTENSION, outExt, 0));
	}

	if((fileOut = fopen(pathOut, "wb")) == NULL){
		exit(error(ERR_CANNOT_CREATE_OUT_FILE, pathOut, 0));
	}
	return fileOut;
}

uint16_t R_instruction(InstructionCode code, FILE* file){

	uint16_t inst, reg1, reg2, reg3;
	char r1[3], r2[3], r3[3];

	line += getFileWord2(file, r1);
	line += getFileWord2(file, r2);
	line += getFileWord2(file, r3);

	if(!isRegister(r1)){
		error(ERR_NOT_VALID_REGISTER, r1, line);
		return NOP;
	}
	if(!isRegister(r2)){
		error(ERR_NOT_VALID_REGISTER, r2, line);
		return NOP;
	}
	if(!isRegister(r3)){
		error(ERR_NOT_VALID_REGISTER, r3, line);
		return NOP;
	}

	inst = (uint16_t)(code << 12);
	reg1 = numRegister(r1) << 10;
	reg2 = numRegister(r2) <<  8;
	reg3 = numRegister(r3) <<  6;

	return inst | reg1 | reg2 | reg3;
}

uint16_t M_instruction(InstructionCode code, FILE* file, Label* labels){

	uint16_t inst, reg1, mem;
	char r1[3], lbl[MAX_LEN_LABEL];

	line += getFileWord2(file, r1);
	line += getFileWord2(file, lbl);

	if(!isRegister(r1)){
		error(ERR_NOT_VALID_REGISTER, r1, line);
		return NOP;
	}
	if(!isLabel(labels, lbl)){
		error(ERR_LABEL_NOT_DECLARED, lbl, line);
		return NOP;
	}

	inst = (uint16_t)(code << 12);
	reg1 = numRegister(r1) << 10;
	mem = getAddress(labels, lbl);

	return inst | reg1 | mem;
}

uint16_t J_instruction(InstructionCode code, FILE* file, Label* labels){

	uint16_t inst, reg1, reg2, addr;
	char r1[3], r2[3], lbl[MAX_LEN_LABEL];

	if(code == JMP){
		reg1 = 0;
		reg2 = 0;
	}else{
		line += getFileWord2(file, r1);
		line += getFileWord2(file, r2);

		if(!isRegister(r1)){
			error(ERR_NOT_VALID_REGISTER, r1, line);
			return NOP;
		}
		if(!isRegister(r2)){
			error(ERR_NOT_VALID_REGISTER, r2, line);
			return NOP;
		}

		reg1 = numRegister(r1) << 10;
		reg2 = numRegister(r2) <<  8;
	}

	line += getFileWord2(file, lbl);
	if(!isLabel(labels, lbl)){
		error(ERR_LABEL_NOT_DECLARED, lbl, line);
		return NOP;
	}else{
		addr = getAddress(labels, lbl);
		addr = addr >> 1;
	}

	inst = (uint16_t)(code << 12);
	//printf("\n[%d | %d | %d | %d]", inst, reg1, reg2, addr);
	return inst | reg1 | reg2 | addr;
}

uint16_t O_instruction(InstructionCode code, FILE* file, Label* labels){

	uint16_t inst, operator, addr;
	char op[MAX_LEN_LABEL];

	line += getFileWord2(file, op);

	if(isRegister(op)){
		operator = numRegister(op) << 8;
		addr = 2048; // enderecamento tipo1
	}
	else if(isLabel(labels, op)){
		operator = getAddress(labels, op);
		addr = 0; // enderecamento tipo2
	}
	else{
		error(ERR_LABEL_NOT_DECLARED, op, line);
		return NOP;
	}

	inst = (uint16_t)(code << 12);
	return inst | operator | addr;
}

void variablesDeclaration(FILE* file, uint8_t memory[], uint16_t* PC, char* goal){
	
	char word[30];
	*PC = 2;

	while(!feof(file)){
		line += getFileWord2(file, word);

		if(isInstruction(word)){
			strcpy(goal, word);
			break;
		}

		toUpper(word);
		if(strcmp(word, "WORD")==0){
			line += getFileWord2(file, word);

			if(isNumber(word)){
				memory[(*PC)++] = toNumber(word);
			}
			else error(ERR_NOT_INT_VALUE, word, line);
		}
	}

	if((*PC) % 2 == 1){
		(*PC)++;
	}
}

ErrorCode loadOutFile(FILE* file, uint8_t memory[]){
	for(int i = 0; i < MEMORY_LEN; i++){

		if(!fwrite(&(memory[i]), sizeof(memory[0]), 1, file)){
			return ERR_UNKNOWN;
		}
	}
	return SUCCESS;
}

void printMemory(uint8_t memory[]){

	printf("\n\t|___Memory____|");
	for(int i = 0; i < MEMORY_LEN; i++){
		printf("\n\t| %03d | %05d |", i, memory[i]);
	}
}

void pushMemory(uint8_t memory[], uint16_t instruction, uint16_t PC){

	uint8_t byte1 = instruction >> 8; 
	uint8_t byte2 = instruction & 0b11111111;

	memory[PC] = byte1;
	memory[PC+1] = byte2;
}
