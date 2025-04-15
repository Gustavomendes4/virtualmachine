#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum Token{
    NoToken,
    LIB,
    VM,
    ASSEMBL,

    _Last_Token_
}Token;

char* tokenList[] = {
    "",
    "lib",
    "VM",
    "assembler",
    "\0"
};

const char* virtualMachine = "VirtualMachine";
const char* assembler = "Assembler";
const char* files[] = {
    "error",
    "file",
    "utils",
    "instruction",
    "label",
    "register",

    "\0",
};

Token getToken(char* str);
void compLib();
void compAssembl();
void compVM();

int main(int argc, char* argv[]){

    if(argc == 1){
        puts("Not enough argumet.");
        return 0;
    }

    switch(getToken(argv[1])){

        case LIB:   compLib();  break;
        case VM:    compVM();   break;
        case ASSEMBL:compAssembl(); break;

        default:{
            puts("Token not identified, compilation termined");
        }
    }
    return 1;
}

void compLib(){

    int i;
    char command[200];

    for(i = 0; files[i][0] != '\0'; i++){ // Cria arquivos .o
        strcpy(command, "gcc ../src/");
        strcat(command, files[i]);
        strcat(command, ".c -c -o ");
        
        strcat(command, files[i]);
        strcat(command, ".o");

        #ifdef DEBUG
            printf("\n%s", command);
        #else
            system(command);
        #endif
       
    }

    strcpy(command, "ar rcs ../build/lib.a ");
    for(i = 0; files[i][0] != '\0'; i++){ // Cria arquivo .a
        strcat(command, "./");
        strcat(command, files[i]);
        strcat(command, ".o ");
    }
        #ifdef DEBUG
            printf("\n%s", command);
        #else
            system(command);
        #endif

    for(i = 0; files[i][0] != '\0'; i++){ // Remove arquivos .o
        strcpy(command, "del ");
        strcat(command, files[i]);
        strcat(command, ".o");
        
        #ifdef DEBUG
            printf("\n%s", command);
        #else
            system(command);
        #endif
    }

    puts("lib.a compiled !");
}

void compVM(){

    FILE* f = fopen("../build/lib.a", "rb");
    char command[100];

    if(f == NULL){
        puts("error: lib.a not found to compilation");
        return;
    }

    strcpy(command, "gcc ../src/");
    strcat(command, virtualMachine);
    strcat(command, ".c ../build/lib.a -o VM");

    #ifdef DEBUG
        printf("%s\n", command);
    #else
        system(command);
    #endif

    puts("Virtual Machine compiled !");
}

void compAssembl(){

    puts("Assembler compiled !\n");
}

Token getToken(char* str){

    if(str == NULL || str [0] == '\0'){
        return NoToken;
    }

    for(Token i = 0; i < _Last_Token_; i ++){
        if(strcmp(tokenList[i], str) == 0){
            return i;
        }
    }

    return NoToken;
}
