#ifndef ASM_H
#define ASM_H

#include <stdio.h>
#include <ctype.h>

#include "work_with_text.h"
#include "stack.h"
#include "colors.h"
#include "commands_code.h"

#define LABEL_SIZE 10

// #define DEBUG_ASSEMBLER

typedef struct {
    char label_name[30];
    int label_value;
} Label_t;

typedef struct {
    const char* command_name;
    size_t      command_hash;
    size_t      command_size;
    COMMANDS    command_code;
    // void (*command_func) (Processor_t*);
} Command_t;

typedef struct {
    Label_t label[LABEL_SIZE];
    int     label_index;
    int     label_count;
} Assembler_t;

typedef struct {
    char*   buffer;
    int     count_element;
    Stack_t stack;
    char* cmdStr;
} Compile_t;

void Compile(const char* commandfile, Assembler_t* assrembler, Command_t* arr_command);

void WriteBiteCodeFile(FILE* bitecode, StackElement_t* arr, size_t count_element);

void CompileCtor(const char* commandfile, Compile_t* compile_struct);
void CompileDtor(Compile_t* compile_struct);

size_t CountHash(const char* string);

int Assembler_Push         (Compile_t* compile_struct);
int Assembler_Write_label  (Assembler_t* assembler, Compile_t* compile_struct);
int Assembler_Jump         (Assembler_t* assembler, Compile_t* compile_struct);
int Assembler_Register_Arg (Compile_t* compile_struct);
int Assembler_RAM          (Compile_t* compile_struct);
int Assembler_get_arg      (Assembler_t* assembler, Compile_t* compile_struct, int command_index);

int Assembler_Search_Command (Assembler_t* assembler, Compile_t* compile_struct, int* i, Command_t* arr_command);

#ifdef DEBUG_ASSEMBLER
    #define ONDEBUGASM(func) func
#else
    #define ONDEBUGASM(func)
#endif

#define PRINT_DEBUG(COLOR, ...) ONDEBUGASM(printf(COLOR "%s:%d ", __FILE__, __LINE__); printf(__VA_ARGS__); printf(RESET))

#define BREAK if (err) break;

#define ADD_ARR_COMMANDS(name, comm_name, size, code)       name[code].command_name = comm_name;               \ 
                                                            name[code].command_hash = CountHash(comm_name);    \
                                                            name[code].command_size = size;                    \
                                                            name[code].command_code = code;
                                                                         
                                                                            
#endif