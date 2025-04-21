#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/utils.h"
#include "../include/error.h"

const char* errorMessages[] = {
    "Finished succesfully",         //SUCCESS,
    "",                             //ERR_UNKNOWN,
    "No input argument",            //ERR_NO_ARGUMENT,
    "Invalid argument",             //ERR_INVALID_ARGUMENT,
    "File extension not accepted",  //ERR_INVALID_EXTENSION,
    "Input file cannot be found",   //ERR_FILE_NOT_FOUND,
    "Uncognize error code",          //ERR_INVALID_OUT_EXTENSION,

    "Cannot create out file '%s'",//ERR_CANNOT_CREATE_OUT_FILE,

    "Used label '%' it not declared",//ERR_LABEL_NOT_DECLARED,
    "Empty label declaration",//ERR_EMPTY_LABEL,
    "The label '%' exceeds the maximum allowed length",//ERR_LONGER_LABEL,
    "The label '%' is already declared",//ERR_REDECLARE_LABEL,
    "Label name ('%') cannot be the same as a register name",//ERR_REGISTER_NAMED_LABEL,
    "Label name ('%') cannot be the same as instruction",//ERR_INSTRUCT_NAMED_LABEL      
    
    "Expected an intenger. '%' is not valid value",//ERR_NOT_INT_VALUE,
    
    "'%' is not a valid instruction",//ERR_NOT_A_INSTRUCTION,
    
    "'%' is not a valid register",//ERR_NOT_VALID_REGISTER,
    
    "Program is logger than memory, the limit is % words",//ERR_PROGRAM_LONGER,
};

Error* errorList = NULL;

ErrorCode error(ErrorCode error, char* arg, int line){

    if(isFatalError(error)){
        printf("%s", errorMessages[error]);
        printf(".\nassemble termined\n");
        return error;
    }

    else{
        Error er = newError(error, arg, line);
        pushError(er);
        return error;
    }
}

int isFatalError(ErrorCode code){

    if(code >= SUCCESS && code <= ERR_FILE_NOT_FOUND)
        return 1;
    
    else{
        return 0;
    }
}

void pushError(Error error){

    Error* iter = errorList;
    Error* novo = (Error*)malloc(sizeof(Error));
    *novo = error;

    if(errorList == NULL){
        errorList = novo;
    }
    else{
        while(iter->nxt){
            iter = iter->nxt;
        }
        iter->nxt = novo;
    }
}

Error newError(ErrorCode code, char* arg, int line){
    Error nErr;

    nErr.code = code;
    nErr.line = line;
    nErr.nxt = NULL;

    strcpy(nErr.msg, errorMessages[code]);
    insertStringAtPercent(nErr.msg, arg);

    return nErr;
}

void printErrorList(){

    Error* iter = errorList;

    if(iter == NULL)
        return;

    printf("\n _____________________________________________________________________\n");
    printf(  "|                            Lista de Erros                           |");
    printf("\n|__Line_.__Cod___.________________________Msg_________________________|");
    printf("\n|       |        |                                                    |");
    
    while(iter){
        printf("\n|-> %03d |   %02d   | %-50s |", iter->line, iter->code, iter->msg);
        iter = iter->nxt;
    }

    printf("\n|_______|________|____________________________________________________|\n");

}

int errorListIsEmpty(){
    return errorList == NULL;
}
