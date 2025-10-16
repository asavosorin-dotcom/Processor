#ifndef CALC_H
#define CALC_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "Logfile.h"
#include "stack.h"
#include "colors.h"

// #define DEBUG

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
    JB_G    = 11,
    JBE_G   = 12,
    JA_G    = 13,
    JAE_G   = 14,
    JE_G    = 15,
    JNE_G   = 16,
    J_G     = 17,
    CALL_G  = 18,
    RET_G   = 19,
    PUSHM_G = 20,
    POPM_G  = 21
};

typedef struct {
    Stack_t         stack;
    StackElement_t* code;
    StackElement_t  registers[8];
    size_t          counter;
    Stack_t         ReturnStack;
    int*            RAM;
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