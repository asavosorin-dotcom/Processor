#ifndef CALC_H
#define CALC_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "Logfile.h"
#include "stack.h"
#include "colors.h"
#include "processor.h"

int add(Stack_t* stk);
int sub(Stack_t* stk);
int mul(Stack_t* stk);
int div(Stack_t* stk);
int sqr(Stack_t* stk);

void Calculate(Processor_t* processor);

#define ADD(stk)  add(&stk)
#define SUB(stk)  sub(&stk)
#define MUL(stk)  mul(&stk)
#define DIV(stk)  div(&stk)
#define SQRT(stk) sqr(&stk)

#define CALCULATE(processor) Calculate(&processor) 

#endif