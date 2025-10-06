#ifndef CALC_H
#define CALC_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "Logfile.h"
#include "stack.h"
#include "colors.h"

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
};

typedef struct {
    Stack_t         stack;
    StackElement_t* code;
    StackElement_t  registers[8];
} Processor_t;

typedef struct {
    COMMANDS command;
    int (*func) (Processor_t*);
} Processor_command_t;

int ProcessorPush (Processor_t* processor);
int ProcessorOut  (Processor_t* processor);
int ProcessorAdd  (Processor_t* processor);
int ProcessorSub  (Processor_t* processor);
int ProcessorMul  (Processor_t* processor);
int ProcessorDiv  (Processor_t* processor);
int ProcessorSqr  (Processor_t* processor);
int ProcessorIn   (Processor_t* processor);
int ProcessorPopr (Processor_t* processor);
int ProcessorPushr(Processor_t* processor);

void Calculate(Processor_t* processor);

extern Processor_command_t arr_command[50];

#define ADD(stk)  add(&stk)
#define SUB(stk)  sub(&stk)
#define MUL(stk)  mul(&stk)
#define DIV(stk)  div(&stk)
#define SQRT(stk) sqr(&stk)

#define CALCULATE(processor) Calculate(&processor) 

#endif