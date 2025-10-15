#ifndef ASM_H
#define ASM_H

#include <stdio.h>
#include <ctype.h>

#include "work_with_text.h"
#include "stack.h"
#include "colors.h"

// #define DEBUG_ASSEMBLER

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
    JB_G    = 11,
    JBE_G   = 12,
    JA_G    = 13,
    JAE_G   = 14,
    JE_G    = 15,
    JNE_G   = 16,
    J_G     = 17 
};

typedef struct {
    char label_name[10];
    int label_value;
} Label_t;

typedef struct {
    const char* command_name;
    size_t      command_size;
    COMMANDS    command_code;
    // void (*command_func) (Processor_t*);
} Command_t;

typedef struct {
    Label_t label[10];
    int     label_index;
} Assembler_t;

void Compile(const char* commandfile, Assembler_t* assrembler);

void WriteBiteCodeFile(FILE* bitecode, StackElement_t* arr, int count_element);

#endif