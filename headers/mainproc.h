#ifndef _MAINPROC_H_
#define _MAINPROC_H_

#include <stdio.h>
#include <ctype.h>

#include "processor.h"
// #include "bite.h"
#include "Logfile.h"
#include "stack.h"
#include "work_with_text.h"

void ProcessorCtor(Processor_t* processor);
void ProcessorDtor(Processor_t* processor);

StackElement_t* TextConvertToBite(const char* filename);

#endif