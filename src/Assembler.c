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

FILE* processInputFile(int argc, char* argv[]);
FILE* processOutputFile(int argc, char* argv[]);

int main(int argc, char* argv[]){

	FILE *fileIn  = processInputFile(argc, argv);
	FILE *fileOut = processOutputFile(argc, argv);

	if(fileIn == NULL || fileOut == NULL)
		return -1;

	return process(fileIn, fileOut);
}

int process(FILE* file, FILE* fileOut){

	Label* labels = createLabelList(file);
	
	//printLabelList(labels);
	//printErrorList();
	//printAllWord(file, labels);

	char ch = 1, word[30];
	int i = 0;

	while(!feof(file)){
		ch = getFileChar(file);

		//putchar(ch);
	}


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
	if(!extensionAccepted(ext)){
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
	printf("\narquivo criado: %s\n", pathOut);
	return fileOut;
}
