#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/utils.h"
#include "../include/file.h"
#include "../include/error.h"
#include "../include/label.h"
#include "../include/instruction.h"
#include "../include/register.h"

void printAllWord(FILE* file, Label* labels);

int process(FILE* file, FILE* fileOut);

int main(int argc, char* argv[]){

	FILE *file, *fileOut;
	char __input[_MAX_PATH];
	char __output[_MAX_PATH];
	char* path = __input;
	char* pathOut = __output;

	if(argc == 1){ // Input File
		return error(ERR_NO_ARGUMENT, "", 0);
		//strcpy(path, "../test.txt");
	}
	else{
		path = argv[1];
	}

	char* ext = getFileExtension(path);
	if(!extensionAccepted(ext)){
		return error(ERR_INVALID_EXTENSION, ext, 0);
	}

	if(argc >= 3){ // Output File
		pathOut = argv[2];
		char* outExt = getFileExtension(pathOut);

		if(outExt){
			if(strcmp(outExt, OUTPUT_EXTENSION) != 0){
				return error(ERR_INVALID_OUT_EXTENSION, outExt, 0);
			}
		}
		else{
			strcat(pathOut, OUTPUT_EXTENSION);
		}
	}
	else{
		pathOut = __output;
		outputFileName(pathOut, path);
	}

	if((file = fopen(path, "rw")) == NULL){
		return error(ERR_FILE_NOT_FOUND, path, 0);
	}

	if((fileOut = fopen(pathOut, "w")) == NULL){
		return error(ERR_CANNOT_CREATE_OUT_FILE, path, 0);
	}

	return process(file, fileOut);
}

int process(FILE* file, FILE* fileOut){

	Label* labels = createLabelList(file);
	
	//printLabelList(labels);
	printErrorList();
	//printAllWord(file, labels);
//------------------------------------

	char ch = 1, word[30];
	int i = 0;

	if(0)
	while(!feof(file)){
		getFileWord(file, word);
		//printf("\n\t%-10s", word);

		if(isInstruction(word)){
			//fprintf(fileOut, "%s | ", word);
			instructionBin(word);
			fprintf(fileOut, "%s", word);
		}

		else if(isLabel(labels, word)){
			fprintf(fileOut, "%s", word);
		}

		else if(isNumber(word)){
			;
		}

		else if(isRegister(word)){
			;
		}

		else{
			;//trata uma expressao desconhecida
		}
	}

	return SUCCESS;
}

void printAllWord(FILE* file, Label* labels){

	char word[30];

	while(!feof(file)){
		getFileWord(file, word);

		printf("\n\t'%-10s'", word);
		if(isLabel(labels, word)){
			printf("| label");
		}
			
		else if(isLabelDeclaration(labels, word)){
			printf("| label declaration");
		}
				
		else if(isInstruction(word)){
			printf("| instruction");
		}
					
		else if(isNumber(word)){
			printf("| number");
		}

		else if(isRegister(word)){
			printf("| register");
		}

		else if(isLiteral(word)){
			printf("| Literal");
		}
/*		
		else{
			TypeOperator type = typeOfOperator(word);

			switch(type){
				case DIRECT: printf("| Direct operator"); break;
				case IMMEDIATE: printf("| Immediaate operator"); break;
				case REGISTER: printf("| Register operator"); break;
				case INDIRECT: printf("| Indirect operator"); break;
			}
		}
		*/
	}
	rewind(file);
}