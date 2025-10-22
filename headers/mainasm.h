#ifndef _MAINPROC_H_
#define _MAINPROC_H_

#include <stdio.h>

#include "asm.h"
#include "stack.h"
#include "colors.h"

void AssemblerCtor(Assembler_t* assembler);
void Assembler_Init_arr_command(Command_t* arr_command);

#define ADD_COMMAND(name, string, size, code) name[code].command_name = string; \
                                              name[code].command_size = size  ;  \
                                              name[code].command_code = code  ;

#endif