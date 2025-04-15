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

    "Used label '%' was not declared",//ERR_LABEL_NOT_DECLARED,
    "Empty label declaration",//ERR_EMPTY_LABEL,
    "The label '%' exceeds the maximum allowed length",//ERR_LONGER_LABEL,
    "The label '%' is already declared",//ERR_REDECLARE_LABEL,
    "Label name ('%') cannot be the same as a register name",//ERR_REGISTER_NAMED_LABEL,
    "Label name ('%') cannot be the same as instruction",//ERR_INSTRUCT_NAMED_LABEL      
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

    printf("\n\n===== Lista de Erros =====");
    
    while(iter){
        printf("\n[%03d]: %02d | %s", iter->line, iter->code, iter->msg);
        iter = iter->nxt;
    }

    printf("\n==========================\n");

}