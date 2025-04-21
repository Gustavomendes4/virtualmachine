#ifndef FILE_H_DEFINED
#define FILE_H_DEFINED

#include "utils.h"

#define EXTENSION_SIZE 7
#define OUTPUT_EXTENSION ".bin"

char* scanFilePath(char *inpt);

char* getFileExtension(char* path);

int extensionAccepted(char* ext, int type);

char getFileChar(FILE* f);

int getFileWord(FILE* file, char* goal);
int getFileWord2(FILE* file, char* goal);

void outputFileName(char* output, char* path);

#endif