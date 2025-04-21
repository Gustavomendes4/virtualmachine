#ifndef REGISTER_H_DEFINED
#define REGISTER_H_DEFINED

int isRegister(char* str);
uint16_t numRegister(char* str);
int isLiteral(char* str);
void printRegisters(uint8_t registerFile[]);

#endif