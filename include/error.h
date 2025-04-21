#ifndef ERROR_H_DEFINED
#define ERROR_H_DEFINED

typedef enum ErrorCode{

    //  General
    SUCCESS,
    ERR_UNKNOWN,
    
    //  File
    ERR_NO_ARGUMENT,
    ERR_INVALID_ARGUMENT,
    ERR_INVALID_EXTENSION,
    ERR_FILE_NOT_FOUND,

    ERR_INVALID_OUT_EXTENSION,
    ERR_CANNOT_CREATE_OUT_FILE,

    //  Label
    ERR_LABEL_NOT_DECLARED,
    ERR_EMPTY_LABEL,
    ERR_LONGER_LABEL,
    ERR_REDECLARE_LABEL,
    ERR_REGISTER_NAMED_LABEL,
    ERR_INSTRUCT_NAMED_LABEL,

    //  variables
    ERR_NOT_INT_VALUE,

    //  Instrutions
    ERR_NOT_A_INSTRUCTION,

    //  Register
    ERR_NOT_VALID_REGISTER,

    //  loader
    ERR_PROGRAM_LONGER,
    
}ErrorCode;

typedef struct Error{
    ErrorCode code;
    char msg[60];
    unsigned int line;

    struct Error* nxt;
}Error;

ErrorCode error(ErrorCode error, char* arg, int line);

int isFatalError(ErrorCode code);

void pushError(Error error);

void printErrorList();

Error newError(ErrorCode code, char* arg, int line);

int errorListIsEmpty();

#endif