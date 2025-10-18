#ifndef _STACK_H_
#define _STACK_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "colors.h"
#include "Logfile.h"

// #define DEBUG
// #define HASH
// #define CANARY

#ifdef DEBUG
    #define ONDEBAG(func) func

    #define ERRPRINTOK(str) err = STACKVERIFY(stk);     \
                                                        \
    if (!err)                                           \
        fprintf(fileerr, str);                          \
    else                                                \
        return err;                                     \
    

#else 
    #define ONDEBAG(func) 
    #define ERRPRINTOK(str) 
#endif

#ifdef CANARY
    #define ONDEBAGCANARY(func) func
#else
    #define ONDEBAGCANARY(func) 
#endif

#ifdef HASH
    #define ONDEBAGHASH(func) func
#else
    #define ONDEBAGHASH(func)
#endif

typedef int StackElement_t;
#define TYPEELEM "%d"

enum StackErr_t {STACK_OK           = 0, 
                 ERR_SIZE           = 1, 
                 ERR_ELEM           = 2, 
                 ERR_STACK_ADRESS   = 4, 
                 ERR_DATA_ADRESS    = 8, 
                 ERR_KANAREYKALEFT  = 16, 
                 ERR_KANAREYKARIGHT = 32, 
                 ERR_CAPASITY       = 64, 
                 ERR_CANARY_STRUCT  = 128,
                 ERR_HASH           = 256,
                 STACK_EMPTY        = 512};
    
typedef struct {
    int line;
    const char* filename;
    const char* funcname;
} Passport_t;
    
typedef struct {
    ONDEBAG(StackElement_t canary_left); // условная компилляция
    ONDEBAG(size_t NumOfStack);
    ONDEBAGHASH(size_t hash);

    StackElement_t* data;
    size_t size;
    int capasity; 

    ONDEBAG(Passport_t passport);
    ONDEBAG(StackElement_t canary_right);
    
} Stack_t;

int StackCtor   (Stack_t* stk, int capasity, int line, const char* stackname, const char* funcname);
int StackPush   (Stack_t* stk, StackElement_t elem, int line);
int StackPop    (Stack_t* stk, StackElement_t* elem, int line);
int StackDtor   (Stack_t* stk, int line);
int StackDump   (Stack_t* stk, int err);
int StackTop    (Stack_t* stk, StackElement_t* elem, int line);
int StackVerify (Stack_t* stk, int line, const char* funcname);
int StackRealloc(Stack_t* stk, int line);
int StackPrint  (Stack_t* stk, int line);

void ReallocArrPointData(void);


size_t StackHash(Stack_t* stk);
 
#ifdef DEBUG
#define STACKVERIFY(stk) StackVerify(stk, line, __func__);
#endif

#define INITSTACK(stk, capasity) StackCtor(&stk, capasity, __LINE__, #stk, __func__);

#define PUSH(stk, elem) StackPush(&stk, elem, __LINE__);
#define POP(stk, elem)  StackPop(&stk, &elem, __LINE__);
#define TOP(stk, elem)  StackTop(&stk, &elem, __LINE__);
#define REALLOC(stk)    StackRealloc(&stk, __LINE__);
#define DTOR(stk)       StackDtor(&stk, __LINE__);
#define PRINTSTACK(stk) StackPrint(&stk, __LINE__);
#define PRINTELEM(elem) printf(BOLD_BLUE TYPEELEM"\n" RESET, elem);

const StackElement_t POISON    = 0xDEDDEAD;
const StackElement_t KANAREYKA = 0xDEADCA;

#endif