#ifndef ASM_H
#define ASM_H

#include <stdio.h>
#include <ctype.h>

#include "work_with_text.h"
#include "stack.h"
#include "processor.h"

void ConvertToBite(const char* commandfile);
void WriteBiteCodeFile(FILE* bitecode, StackElement_t* arr, int count_element);

#endif