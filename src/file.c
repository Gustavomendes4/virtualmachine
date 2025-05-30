#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/file.h"
#include "../include/error.h"

char* acceptedExtInput[] = {
	".txt",

	"\0",
};

char* acceptedExtOutput[] = {
	".bin",

	"\0",
};

char* scanFilePath(char* inpt){
	printf("Input a file-> ");
	scanPath(inpt, _MAX_PATH);
	return inpt;
}

char* getFileExtension(char* path){

    int i = 0;

    while(path[i] != '\0'){
        i++;
    }
    
    while(path[i] != '.'){
        i--;

		if(i == 0 || path[i] == '/' || path[i] == '\\'){
			return NULL;
		}
    }
    
    return &path[i];
}

int extensionAccepted(char* ext, int type){

	char** extensions = (type == 0) ? acceptedExtOutput : acceptedExtInput;

	for(int i = 0; extensions[i][0] != '\0'; i++){
		if(strcmp(ext, extensions[i]) == 0){
			return 1;
		}
	}
    return 0;
}

char getFileChar(FILE* f){

	char ch = fgetc(f);

	if(ch == ';'){
		while(ch != '\n' && ch != EOF){
			ch = fgetc(f);
			//printf("\n%d", ch);
		}
	}
	
	return ch;
}

int getFileWord(FILE* file, char* goal){

	int i = 0, line = 0;
	char ch, word[60];
	goal[0] = '\0';

	while(!feof(file)){
		ch = getFileChar(file);

		if(ch == ':'){
			word[i++] = ch;
			word[i] = '\0';
			strcpy(goal, word);
			return line;
		}

		if(ch == '\t' || ch == ','){
			ch = ' ';
		}

		else if(ch == '\n'){
			line++;
			ch = ' ';
		}

		if(ch != ' '){
			word[i++] = ch;
			word[i] = '\0';
		}

		else{
			if(word[0] == '\0'){
				i = 0;
			}

			else{
				strcpy(goal, word);
				return line;
			}
		}
	}
	strcpy(goal, word);
	return line;
}

int getFileWord2(FILE* file, char* goal){

	char ch;
	int i = 0, line = 0;

	while(1){
		ch = getFileChar(file);

		if(ch == '\n'){
			ch = ' ';
			line++;
		}

		if(ch == ':'){
			goal[i++] = ch;
			goal[i] = '\0';
			return line;
		}

		if(ch == EOF || ch == ' ' || ch == ':'){
			if(i > 0 || ch == EOF){
				goal[i] = '\0';
				break;
			}
			continue;
		}
		goal[i] = ch;
		i++;
	}
	return line;
}

void clearFile(FILE* file){
	;
}

void outputFileName(char* output, char* path){

	int i = 0;

	strcpy(output, path);
	char* ext = getFileExtension(output);

	if(ext){
		*ext = '\0';
		strcat(output, OUTPUT_EXTENSION);
	}

}
