#ifndef CALC_H
#define CALC_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "Logfile.h"
#include "stack.h"

int add(Stack_t* stk);
int sub(Stack_t* stk);
int mul(Stack_t* stk);
int div(Stack_t* stk);
int sqr(Stack_t* stk);

void Calculate(Stack_t* stk1, StackElement_t* arr);

#define ADD(stk) add(&stk)
#define SUB(stk) sub(&stk)
#define MUL(stk) mul(&stk)
#define DIV(stk) div(&stk)
#define SQRT(stk) sqr(&stk)
#define CALCULATE(stk, arr) Calculate(&stk, arr) 

#endif