#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <math.h>

#include "../include/utils.h"

#define NaN -101

int vDate(int dia, int mes, int ano){ //Valida uma data recebida
	
	int aprovado = 0;
	
	switch(mes){
		case 1:	case 3: case 5: case 7: case 8: case 10: case 12:
			if(dia > 31) aprovado = 1;
		break;
		
		case 4: case 6: case 9: case 11:
			if(dia > 30) aprovado = 1;
		break;
		
		case 2:
			if(ano % 4 == 0){ if(dia > 29) aprovado = 1;}
			else if(dia > 28) aprovado = 1;
			break;
			
		default: aprovado = 1;
	}
	
	if(dia < 1) aprovado = 1;
	return aprovado;
}

void scanString(char *str, int len){
	char c = 0;
	int i = 0;
	
	do{
		c = getch();
		
		if(((c > 64 && c < 91) || (c >= 'a' && c <= 'z') || c == ' ') && i < len - 1){
			str[i++] = c;
			putchar(c);
		}
		else if(c == '\b' && i > 0){
			printf("\b \b");
			i--;
		}	
	}while(c != 13);	
	str[i] = '\0';
}

void scanPath(char *str, int len){
	char c = 0;
	int i = 0;
	
	do{
		c = getch();
		
		if(((c > 64 && c < 91) || (c >= 'a' && c <= 'z') || c == ' ' || c == '.' || c == '_' || c == '/') && i < len - 1){
			str[i++] = c;
			putchar(c);
		}
		else if(c == '\b' && i > 0){
			printf("\b \b");
			i--;
		}	
	}while(c != 13);	
	str[i] = '\0';
}

float getFloat(){
	char c, alt[7];
	int i = 0, pont = 0;
	float ret=0, signal = 1;
	
	for(i = 0; i < 6; i++) alt[i] = 48;
	i=0;
	
	do{
		c = getch();
		if(c > 47 && c < 58 && i < 6){
			alt[i] = c;
			i++;
			printf("%c", c);
		}
		else if((c == '.' || c== ',') && i > 0 && i < 6 && pont == 0){
			printf(".");
			pont = i;
		}
		
		else if(c == '-' && i == 0){
			putchar(c);
			signal = -1;
		}
		
		else if(c == 8){
			if(i > 0){
				printf("\b \b");
				
				if(i == pont)
				pont = 0;
			else
				alt[--i] = 48;
			}
			else{
				printf("\b \b");
				signal = 1;
			}

		}
	}while(c != 13);

// Convete de CHAR para INT
	for(i = 0; i < 6; i++) alt[i] -= 48;
	
// Converte do vetor para float
	for(i = 0; i < 6; i++) ret += (float)alt[i] * 100000 / pow(10, i);
	pont = 6 - pont;
	ret /= pow(10, pont);
	
	return ret * signal;
}

void getDate(int *dia, int *mes, int *ano){
	char c, alt[8];
	int i = 0;
			
	do{
		c = getch();
		if(c > 47 && c < 58 && i < 8){
			alt[i] = c;
			i++;
			printf("%c", c);
				
			if(i == 2 || i == 4) printf("/");
		}
			
		else if(c == 8 && i > 0){
			printf("%c", c);
			printf(" ");
			printf("%c", c);
			i--;
				
			if(i == 1 || i == 3){
				printf("%c", c);
				printf(" ");
				printf("%c", c);
			}
		}
	}while(!(c == 13 && i == 8));
		
//	printf("\n\n");
//	for(i = 0; i < 8; i++) printf("%c", alt[i]); getch();
	for(i = 0; i < 8; i++) alt[i] -= 48;
		
	*dia = alt[0] * 10;
	*dia += alt[1];
	*mes = alt[2] * 10;
	*mes += alt[3];
	*ano = alt[4] * 1000;
	*ano += alt[5] * 100; 
	*ano += alt[6] * 10;
	*ano += alt[7];
}

int getInt(){
	
	char ch = 0;
	int i = 0, vet[4];
	int signal = 1;
	
	while(ch != 13 || i == 0){	
		ch = getch();
		
		if((ch > 47 && ch < 58) && i < 4){
			vet[i++] = ch - 48;
			putchar(ch);
		}
		
		else if(ch == 8){
			
			if(i > 0){
				printf("\b \b");
				--i;
			}
			else if(i == 0 && signal == -1){
				printf("\b \b");
				signal = 1;
			}
		}
		else if(ch == '-' && signal == 1){
			putchar(ch);
			signal = -1;
		}
	}
	
	int mult = 1, ret = 0;
	for(i; i > 0; i){
		ret += vet[--i] * mult;
		mult *= 10;
	}
	return ret * signal;
}

int getCPF(int cpf[11]){
	char c, alt[11];
	int i = 0, aux1 = 0, aux2 = 0;
	
	do{
		c = getch();
		if(c > 47 && c < 58 && i < 11){
			alt[i] = c;
			i++;
			putchar(c);
					
			if(i == 3 || i == 6) printf(".");
			else if(i == 9) printf("-");
		}
		
		else if(c == 8 && i > 0){
			printf("%c %c", c,c);
			i--;
				
			if(i == 2 || i == 5 || i == 8)
				printf("%c %c", c, c);
		}
	}while(!(c == 13 && i == 11));
		
	//validar cpf
	for(i = 0; i < 9; i++)
		aux1 += (alt[i] - 48) * (10 - i);
	aux1 *= 10;
	aux1 %= 11;
	if(aux1 == 10) aux1 = 0;
		
	for(i = 0; i < 10; i++)
		aux2 += (alt[i] - 48) * (11 - i);
	aux2 *= 10;
	aux2 %= 11;
	if(aux2 == 10) aux2 = 0;
	
	for(i = 0; i < 11; i++)
		cpf[i] = alt[i] - 48;
	
	
	if( aux1 != (alt[9] - 48) || aux2 != (alt[10] - 48)) //CPF inv�lido
		return FALSE;
	else
		return TRUE;
}

void getPhone(int *phone){

	char ch;
	int num;
	int vet[11];
	BOOL valid = TRUE;
	
	num = 0;
	putchar('(');
		
	while(ch != 13 || num != 11){
		ch = getch();
				
		if(ch >= 48 && ch <= 57 && num < 11){
			putchar(ch);
			vet[num++] = ch-48;
				
			if(num == 2) printf(")");
			else if	(num == 7) putchar('-');
			}
			else if(ch == '\b' && num > 0){
				printf("\b \b");
				num--;
				
				if(num == 1 || num == 6)
					printf("\b \b");
			}	
	}
	for(num = 0; num < 11; num++)
		phone[num] = vet[num];
}

int valEmail(char* email){

	int i 				= 0;
	int numBeforeAt		= 0;
	int numAfterAt		= 0;
	int numAfterPoint	= 0;
	
	BOOL at				= 0;
	BOOL point			= 0;
	BOOL emailCondition	= 1;
	
	while(email[i] != '\0'){
		
		if(!(email[i] == '-' || email[i] == '.' || (email[i] >= 48 && email[i] <= 57) || (email[i] > 63 && email[i] < 91) || (email[i] > 96 && email[i] < 123) ))
			emailCondition = FALSE;
		
		if(!at){
			(email[i] == '@') ? at = 1 : numBeforeAt++;
		
		}else if(!point){
			(email[i] == '@') ? emailCondition = 0 : (email[i] == '.') ? point = 1 : numAfterAt++;	

		}else{
			(email[i] == '@') ? emailCondition = FALSE : numAfterPoint++;
		}
		i++;
	}
	
	if(numBeforeAt < 5)		emailCondition	= FALSE;
	if(numAfterAt < 3)		emailCondition	= FALSE;
	if(numAfterPoint < 3)	emailCondition	= FALSE;
	
	return emailCondition;
}

void now(int* hora, int* min, int* sec){
	time_t second;
	time(&second);
	struct tm *DHnow = localtime(&second);
	
	*sec = DHnow->tm_sec;
    *min = DHnow->tm_min;
    *hora= DHnow->tm_hour;
}

void today(int* dia, int* mes, int* ano){
	time_t second;
	time(&second);
	struct tm *DHnow = localtime(&second);
	
    *dia = DHnow->tm_mday;
    *mes = DHnow->tm_mon + 1;
    *ano = DHnow->tm_year;
}

void toUpper(char* str){
	
	int i = 0;
	while(str[i]){
		if(str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 32;
		i++;
	}
	
}

void toLower(char* str){
	int i = 0;
	while(str[i]){
		if(str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
		i++;
	}
}

void toTitle(char* str){
	int i = 0;
	
	while(str[i]){
		if((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')){
			if(i == 0 || str[i-1] == ' '){
				if(str[i] > 'Z')
					str[i] -= 32;
			}
			else if(str[i] < 'a')
				str[i]+= 32;
		}
		i++;
	}
}

BOOL isDigit(char digit){
	if(digit < '0' || digit > '9')
		return FALSE;

	else
		return TRUE;
}

int toDigit(char digit){

    if(!isDigit(digit)){
        return NaN;
    }

    return digit - 48;
}

BOOL isNumber(char* numb){

	int i;

    if(numb == NULL || numb[0] == '\0'){
        return FALSE;
    }

	for(i = 0; numb[i] != '\0'; i++){
		if(!isDigit(numb[i])){
			return FALSE;
		}
	}
	return TRUE;
}

int toNumber(char* str){
    
    if(!isNumber(str)){
        return NaN;
    }

    int i = 0;
    int vect[10];
    
	while(str[i] != '\0'){
        vect[i] = toDigit(str[i]);
        i++;
	}

    i--;
    int num = 0, pot = 0;

    while(i >= 0){
        num += vect[i] * pow(10, pot);
        pot++;
        i--;
    }

	return num;
}

void insertStringAtPercent(char* str1, char* str2){

	int pos1 = 0, i;

	int tam1 = strlen(str1);
	int tam2 = strlen(str2);

	if(str1 == NULL || str2 == NULL){
		return;
	}

	for(pos1 = 0; str1[pos1] != '%'; pos1++){ // localiza %
		if(str1[pos1] == '\0'){
			return;
		}
	}

	for(i = tam1; i > pos1; i--){ // Move str1 N casas apartir do %
		str1[i + tam2-1] = str1[i];//<_
	}

	for(i = 0; i < tam2; i++){
		str1[pos1 + i] = str2[i];
	}
}

int16_t invertBytes(int16_t num){

	uint16_t u = (uint16_t)num;

    uint16_t val1 = (u &   255) << 8; // 0000000011111111
    uint16_t val2 = (u & 65280) >> 8; // 1111111100000000

    return val1 | val2;
}
