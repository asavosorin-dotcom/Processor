#ifndef ASM_H
#define ASM_H

#include <stdio.h>
#include <ctype.h>

#include "work_with_text.h"
#include "stack.h"


typedef int Elem_t;
#define ELEMTYPE "%d"

enum COMMANDS{HLT_G  = 0, 
    PUSH_G = 1, 
    MUL_G  = 2, 
    SUB_G  = 3, 
    OUT_G  = 4, 
    DIV_G  = 5, 
    ADD_G  = 6,
    SQRT_G = 7
};
    
    typedef struct {
        const char* command_name;
        size_t      command_size;
        COMMANDS    command_code;
    } Command_t;
    
extern Command_t arr_command[8];

void ConvertToBite(const char* commandfile);
void WriteBiteCodeFile(FILE* bitecode, StackElement_t* arr);

#endif