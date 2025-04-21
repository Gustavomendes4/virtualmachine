/*

	Especifica funções para determinação e mapeamento de flags durante
	o programa.

	Armazena as flags em um lista encadeada.

*/

#ifndef LABEL_H_DEFINED
#define LABEL_H_DEFINED

#include <stdio.h>
#include <stdint.h>
#include "error.h"

#define MAX_LEN_LABEL 30

typedef struct Label{
	char flag[MAX_LEN_LABEL];
	uint16_t address;
	struct Label* nxt;
}Label;

uint16_t getAddress(Label* list, char* lbl);
ErrorCode validateLabelName(Label* list, char* str);
Label* createLabelList(FILE* file);
void pushLabel(Label** list, char* str, int addr);
void printLabelList(Label* list);
int isLabel(Label* list, char* str);
int isLabelDeclaration(Label* list, char* str);

#endif