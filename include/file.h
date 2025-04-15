#ifndef FILE_H_DEFINED
#define FILE_H_DEFINED

#include "utils.h"

#define EXTENSION_SIZE 7
#define OUTPUT_EXTENSION ".out"

char* scanFilePath(char *inpt);

char* getFileExtension(char* path);

int extensionAccepted(char* ext);

char getFileChar(FILE* f);

int getFileWord(FILE* file, char* goal);

void outputFileName(char* output, char* path);

#endif