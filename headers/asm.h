#ifndef ASM_H
#define ASM_H

#include <stdio.h>
#include <ctype.h>

#include "work_with_text.h"
#include "stack.h"
#include "colors.h"
#include "commands_code.h"

// #define DEBUG_ASSEMBLER

typedef struct {
    char label_name[30];
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
    int     label_count;
} Assembler_t;

void Compile(const char* commandfile, Assembler_t* assrembler);

void WriteBiteCodeFile(FILE* bitecode, StackElement_t* arr, int count_element);

#endif