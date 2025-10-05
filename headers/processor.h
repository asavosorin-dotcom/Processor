#ifndef _PROCESSOR_H_
#define _PROCESSOR_H_

#include <stdio.h>
#include "stack.h"

enum COMMANDS{
    HLT_G   = 0 , 
    PUSH_G  = 1 , 
    MUL_G   = 2 , 
    SUB_G   = 3 , 
    OUT_G   = 4 , 
    DIV_G   = 5 , 
    ADD_G   = 6 ,
    SQRT_G  = 7 ,
    IN_G    = 8 ,
    POPR_G  = 9 ,
    PUSHR_G = 10,
};

typedef struct {
    const char* command_name;
    size_t      command_size;
    COMMANDS    command_code;
    // void (*command_func) (Processor_t*);
} Command_t;

typedef struct {
    Stack_t stack;
    StackElement_t* code;
    StackElement_t registers[8];
} Processor_t;

extern Command_t  arr_command[50];

#endif