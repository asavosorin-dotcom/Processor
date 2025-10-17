#ifndef CALC_H
#define CALC_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "Logfile.h"
#include "stack.h"
#include "colors.h"
#include "commands_code.h"

// #define DEBUG

typedef struct {
    Stack_t         stack;
    StackElement_t* code;
    StackElement_t  registers[8];
    size_t          counter;
    Stack_t         ReturnStack;
    int*            RAM;
    size_t          RAM_size;
} Processor_t;

typedef struct {
    COMMANDS command;
    int (*func) (Processor_t*);
} Processor_command_t;

void PrintArr        (int* arr, int number_of_elem);

int ProcessorPush    (Processor_t* processor);
int ProcessorOut     (Processor_t* processor);
int ProcessorAdd     (Processor_t* processor);
int ProcessorSub     (Processor_t* processor);
int ProcessorMul     (Processor_t* processor);
int ProcessorDiv     (Processor_t* processor);
int ProcessorSqr     (Processor_t* processor);
int ProcessorRemdiv  (Processor_t* processor);
int ProcessorIn      (Processor_t* processor);
int ProcessorPopr    (Processor_t* processor);
int ProcessorPushr   (Processor_t* processor);
int ProcessorJump    (Processor_t* processor); 
int ProcessorJump_B  (Processor_t* processor);
int ProcessorJump_BE (Processor_t* processor);
int ProcessorJump_A  (Processor_t* processor);
int ProcessorJump_AE (Processor_t* processor);
int ProcessorJump_E  (Processor_t* processor);
int ProcessorJump_NE (Processor_t* processor);
int ProcessorCall    (Processor_t* processor);
int ProcessorRet     (Processor_t* processor);
int ProcessorPushm   (Processor_t* processor);
int ProcessorPopm    (Processor_t* processor);
int ProcessorDraw    (Processor_t* processor);

void Processor(Processor_t* processor);

extern Processor_command_t arr_command[50];

#define ADD(stk)  add(&stk)
#define SUB(stk)  sub(&stk)
#define MUL(stk)  mul(&stk)
#define DIV(stk)  div(&stk)
#define SQRT(stk) sqr(&stk)

#define CALCULATE(processor) Processor(&processor) 

#ifdef DEBUG
    #define ONDEBUGPROC(func) _FUNCTEXCEPT_H
#else
    #define ONDEBUGPROC(func)
#endif

#endif