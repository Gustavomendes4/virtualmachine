/*

	Especifica funções para determinação e mapeamento de flags durante
	o programa.

	Armazena as flags em um lista encadeada.

*/

#ifndef LABEL_H_DEFINED
#define LABEL_H_DEFINED

#include <stdio.h>
#include "error.h"

#define MAX_LEN_LABEL 30

typedef struct Label{
	char flag[MAX_LEN_LABEL];
	int address;
	struct Label* nxt;
}Label;

ErrorCode validateLabelName(Label* list, char* str);
Label* createLabelList(FILE* file);
void pushLabel(Label** list, char* str, int addr);
void printLabelList(Label* list);
int isLabel(Label* list, char* str);
int isLabelDeclaration(Label* list, char* str);

#endif