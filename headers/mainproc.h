#ifndef _MAINPROC_H_
#define _MAINPROC_H_

// #include "TXLib.h"
#include <stdlib.h>
#include "processor.h"

#include <stdio.h>
#include <ctype.h>

// #include "bite.h"
#include "Logfile.h"
#include "stack.h"
#include "work_with_text.h"

void ProcessorCtor(Processor_t* processor);
void ProcessorDtor(Processor_t* processor);

void Processor_Init_ArrCommand(Processor_command_t* arr_command);

StackElement_t* TextConvertToBite(const char* filename);

#endif