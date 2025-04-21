#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <conio.h>
#include <time.h>
#include <math.h>

#define BOOL  int
#define TRUE  1
#define FALSE 0

int vDate(int dia, int mes, int ano);

void getString(char *str, int len);

void scanPath(char *str, int len);

float getFloat();

void getDate(int *dia, int *mes, int *ano);

int getInt();

int getCPF(int cpf[11]);

void getPhone(int *phone);

int valEmail(char* email);

void now(int* hora, int* min, int* sec);

void today(int* dia, int* mes, int* ano);

void toUpper(char* str);

void toLower(char* str);

void toTitle(char* str);

BOOL isDigit(char digit);

int toDigit(char digit);

int isNumber(char* numb);

int toNumber(char* str);

void insertStringAtPercent(char* str1, char* str2);

int16_t invertBytes(int16_t num);

#endif