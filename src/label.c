#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/label.h"
#include "../include/file.h"
#include "../include/error.h"
#include "../include/instruction.h"
#include "../include/register.h"

ErrorCode validateLabelName(Label* list, char* str){
	
	int i = 0;
	char input[MAX_LEN_LABEL];


	if(str == NULL || str[0] == '\0'){
		return ERR_EMPTY_LABEL;
	}
	else if(isRegister(str)){
		return ERR_REGISTER_NAMED_LABEL;
	}
	else if(isInstruction(str)){
		return ERR_INSTRUCT_NAMED_LABEL;
	}

	while(str[i] != '\0'){
		if(i++ == MAX_LEN_LABEL){
			return ERR_LONGER_LABEL;
		}
	}

	strcpy(input, str);
	toUpper(input);

	while(list){
		if(strcmp(input, list->flag) == 0){
			return ERR_REDECLARE_LABEL;
		}
		list = list->nxt;
	}

	return SUCCESS;
}

Label* createLabelList(FILE* file){

	int i = 0, addr = 0, len, line = 1;
	char word[40];
	word[0] = '\0';

	Label* list = NULL;

	while(!feof(file)){
		line += getFileWord(file, word);

		len = strlen(word);

		if(word[len-1] == ':'){
			word[len-1] = '\0';
			ErrorCode vald = validateLabelName(list, word);
			
			if(vald == SUCCESS){
				pushLabel(&list, word, addr);
			}
			else{
				error(vald, word, line);
			}
		}

		else if(isInstruction(word)){
			addr += 2;// nao considera ORG
		}
	}

	rewind(file);
	return list;
}

void pushLabel(Label** list, char* str, int addr){

	Label* novo = (Label*)malloc(sizeof(Label));
	novo->address = addr;
	novo->nxt = NULL;
	strcpy(novo->flag, str);
	toUpper(novo->flag);

	if(*list == NULL){
		*list = novo;
	}
	else{
		Label* iter = *list;

		while(iter->nxt){
			iter = iter->nxt;
		}

		iter->nxt = novo;
	}
}

void printLabelList(Label* list){

	if(list == NULL){
		return;
	}

	Label* iter = list;

	while(iter){
		printf("\n%p: %s[%d]", iter, iter->flag, iter->address);
		iter = iter->nxt;
	}
}

int isLabel(Label* list, char* str){

	char input[MAX_LEN_LABEL];

	if(list == NULL || strlen(str) > MAX_LEN_LABEL)
		return 0;


	strcpy(input, str);
	toUpper(input);

	while(list){

		if(strcmp(list->flag, input) == 0){
			return 1;
		}

		list = list->nxt;
	}
	return 0;
}

int isLabelDeclaration(Label* list, char* str){

	char inpt[20];
	strcpy(inpt, str);

	int lastPos = strlen(inpt) - 1;

	if(inpt[lastPos] != ':'){
		return 0;
	}

	inpt[lastPos] = '\0';

	return isLabel(list, inpt);
}
