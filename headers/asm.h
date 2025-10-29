#ifndef ASM_H
#define ASM_H

#include "TXLib.h"

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "work_with_text.h"
#include "stack.h"
#include "colors.h"
#include "commands_code.h"

#define LABEL_SIZE 10

// #define DEBUG_ASSEMBLER
// #define DEBUG_LABEL

typedef struct {
    size_t label_hash;
    int    label_value;
} Label_t;

typedef struct {
    const char* command_name;
    size_t      command_hash;
    size_t      command_size;
    COMMANDS    command_code;
} Command_t;

typedef struct {
    Label_t label[LABEL_SIZE];
    int     label_size;
    int     label_index;
    int     label_count;
} Assembler_t;

typedef struct {
    String_t*   arr_string;
    int         count_string;

    int     count_element;
    Stack_t stack;
    char* cmdStr;
} Compile_t;

void Compile(const char* commandfile, Assembler_t* assrembler, Command_t* arr_command);

void WriteByteCodeFile(FILE* bytecode, StackElement_t* arr, size_t count_element);

void CompileCtor(const char* commandfile, Compile_t* compile_struct);
void CompileDtor(Compile_t* compile_struct);

size_t CountHash(const char* string);

int Assembler_Push           (Compile_t* compile_struct, char* string_assembler, int* arg);
int Assembler_Write_label    (Assembler_t* assembler,  Compile_t* compile_struct, char* string_assembler);
int Assembler_Search_Command (Compile_t* compile_struct, Command_t** command, Command_t* arr_command, char* string_assembler);
int Assembler_Register_Arg   (Compile_t* compile_struct, char* string_assembler, int* arg);
int Assembler_RAM            (Compile_t* compile_struct, char* string_assembler, int* arg);
int Assembler_get_arg        (Assembler_t* assembler, Compile_t* compile_struct, Command_t command, char* string_assembler, int* arg);
int Assembler_Jump           (Assembler_t* assembler, Compile_t* compile_struct, char* string_assembler, int* arg);

int compar_label (const void* label_1, const void* label_2);
int compar_command (const void* command_1, const void* command_2);

#ifdef DEBUG_ASSEMBLER
    #define ONDEBUGASM(func) func
#else
    #define ONDEBUGASM(func)
#endif

#define PRINT_DEBUG(COLOR, ...) ONDEBUGASM(printf(COLOR "%s:%d ", __FILE__, __LINE__); printf(__VA_ARGS__); printf(RESET))

#define ARG 2

#define ARR_COMMAND_SIZE 50

#define BREAK if (err) break;

#define ADD_ARR_COMMANDS(name, comm_name, size, code)       name[code].command_name = comm_name;               \
                                                            name[code].command_hash = CountHash(comm_name);    \
                                                            name[code].command_size = size;                    \
                                                            name[code].command_code = code;
                         
enum Comparison_t {ABOVE = 1, EQUAL = 0, BELOW = -1};
                                                                            
#endif