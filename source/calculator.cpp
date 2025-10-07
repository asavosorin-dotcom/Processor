// #include "calculate.h"
#include "calculator.h"

// Считывание файла в буфер с переделыванием code.ASM в исполняемый байт-код
// Байт-код будет храниться в массиве, который нужно создать
// 

Processor_command_t arr_command[50] = { 
                            HLT_G  ,  0,
                            PUSH_G ,  ProcessorPush ,
                            MUL_G  ,  ProcessorMul  ,
                            SUB_G  ,  ProcessorSub  ,
                            OUT_G  ,  ProcessorOut  ,
                            DIV_G  ,  ProcessorDiv  ,
                            ADD_G  ,  ProcessorAdd  ,
                            SQRT_G ,  ProcessorSqr  , 
                            IN_G   ,  ProcessorIn   ,
                            POPR_G ,  ProcessorPopr ,
                            PUSHR_G,  ProcessorPushr,
                            JB_G   ,  ProcessorJumpB,
                            JBE_G  ,  ProcessorJumpBE,
                            JA_G   ,  ProcessorJumpA ,
                            JAE_G  ,  ProcessorJumpAE,
                            JE_G   ,  ProcessorJumpE,
                            JNE_G  ,  ProcessorJumpNE,
};

int ProcessorPush(Processor_t* processor) 
{
    int err = 0;
    
    // //printf("code = %d\n", processor->code[processor->counter]);

    processor->counter++;



    StackElement_t elem = processor->code[processor->counter];
    PUSH(processor->stack, elem);

    processor->counter++;

    //printf("code = %d\n", processor->code[processor->counter]);

    return err;
}

int ProcessorOut(Processor_t* processor) 
{
    StackElement_t elem = processor->code[processor->counter];
    int err = 0;
    err = POP(processor->stack, elem);
    (err != 0) ? printf(RED "Empty Stack\n" RESET) : PRINTELEM(elem)

    processor->counter++;
    // fprintf(fileerr, "%d\n", processor->code[processor->counter]);

    // PRINTSTACK(processor->stack);
    return err;
}
 


int ProcessorAdd(Processor_t* processor) 
{    
    StackElement_t elem1 = 0;
    int err = POP(processor->stack, elem1);

    StackElement_t elem2 = 0;
    err |= POP(processor->stack, elem2);

    err |= PUSH(processor->stack, elem1 + elem2);

    processor->counter++;

    return err;
}

int ProcessorSub(Processor_t* processor) 
{
    StackElement_t elem1 = 0;
    int err = POP(processor->stack, elem1);

    StackElement_t elem2 = 0;
    err |= POP(processor->stack, elem2);

    err |= PUSH(processor->stack, elem2 - elem1);

    processor->counter++;

    return err;
}

int ProcessorMul(Processor_t* processor) 
{
    
    StackElement_t elem1 = 0;
    int err = POP(processor->stack, elem1);

    StackElement_t elem2 = 0;
    err |= POP(processor->stack, elem2);

    err |= PUSH(processor->stack, elem2 * elem1);

    processor->counter++;

    // printf("im in mul\n");

    return err;
}

int ProcessorDiv(Processor_t* processor) 
{
    // printf()
    // PRINTSTACK(processor->stack);
    StackElement_t elem1 = 0;
    int err = POP(processor->stack, elem1);

    StackElement_t elem2 = 0;
    err |= POP(processor->stack, elem2);

    err |= PUSH(processor->stack, elem2 / elem1);

    processor->counter++;

    return err;
}

int ProcessorSqr(Processor_t* processor) 
{    
    StackElement_t elem1 = 0;
    int err = POP(processor->stack, elem1);
    elem1 = (StackElement_t) floor(sqrt(elem1 * pow(10, 6))) / 1000;

    err |= PUSH(processor->stack, elem1);

    processor->counter++;

    return err;
}

int ProcessorIn(Processor_t* processor) 
{
    int err = 0;
    
    printf(BOLD_BLUE "Enter value:\n" RESET);

    StackElement_t val = 0;
    scanf(TYPEELEM, &val);
    err = PUSH(processor->stack, val);

    processor->counter++;

    return err;
}

int ProcessorPopr(Processor_t* processor) 
{
    int err = 0;
    
    StackElement_t val = 0;
    err = POP(processor->stack, val);
    // PRINTELEM(val);
    processor->counter++;

    // printf("code in popr = %d\n", processor->code[processor->counter]);

    processor->registers[processor->code[processor->counter] - 1] = val;
    processor->counter++;

    // printf("code after popr = %d\n", processor->code[processor->counter]);

    return err;
}

int ProcessorPushr(Processor_t* processor) 
{
    int err = 0;
    
    processor->counter++;

    // printf(TYPEELEM"\n", arr_register[arr[i]].register_value);
    err = PUSH(processor->stack, processor->registers[processor->code[processor->counter] - 1]);

    processor->counter++;

    // printf("code after pushr = %d\n", processor->code[processor->counter]);

    return err;
}

//--------------------------------------------------------------JUMP-----------------------------------------------------

// #define IMPL_JUMP(name, op_comparison) int ProcessorJump_#name(Processor_t* processor) \
// {                                                                                      \
//     int err = 0;                                                                       \
//                                                                                         \
//     StackElement_t elem1 = 0;\
//     err = POP(processor->stack, elem1);\
// \
//     StackElement_t elem2 = 0;\
//     err = POP(processor->stack, elem2);\
// \
//     if (elem2 < elem1)\
//         processor->counter = processor->code[processor->counter + 1];\
//     else\
//         processor->counter += 2;\
// \
//     return err;\
// }

int ProcessorJumpB(Processor_t* processor)
{
    int err = 0;

    StackElement_t elem1 = 0;
    err = POP(processor->stack, elem1);

    StackElement_t elem2 = 0;
    err = POP(processor->stack, elem2);

    if (elem2 < elem1)
        processor->counter = processor->code[processor->counter + 1];
    else
        processor->counter += 2;

    // fprintf(fileerr, TYPEELEM "\n", processor->code[processor->counter]);    
    return err;
}

int ProcessorJumpBE(Processor_t* processor)
{
    int err = 0;

    StackElement_t elem1 = 0;
    err = POP(processor->stack, elem1);

    StackElement_t elem2 = 0;
    err = POP(processor->stack, elem2);

    if (elem2 <= elem1)
        processor->counter = processor->code[processor->counter + 1];
    else
        processor->counter += 2;

    // fprintf(fileerr, TYPEELEM "\n", processor->code[processor->counter]);    
    return err;
}

int ProcessorJumpA(Processor_t* processor)
{
    int err = 0;

    StackElement_t elem1 = 0;
    err = POP(processor->stack, elem1);

    StackElement_t elem2 = 0;
    err = POP(processor->stack, elem2);

    if (elem2 > elem1)
        processor->counter = processor->code[processor->counter + 1];
    else
        processor->counter += 2;

    // fprintf(fileerr, TYPEELEM "\n", processor->code[processor->counter]);    
    return err;
}

int ProcessorJumpAE(Processor_t* processor)
{
    int err = 0;

    StackElement_t elem1 = 0;
    err = POP(processor->stack, elem1);

    StackElement_t elem2 = 0;
    err = POP(processor->stack, elem2);

    if (elem2 >= elem1)
        processor->counter = processor->code[processor->counter + 1];
    else
        processor->counter += 2;

    // fprintf(fileerr, TYPEELEM "\n", processor->code[processor->counter]);    
    return err;
}

int ProcessorJumpE(Processor_t* processor)
{
    int err = 0;

    StackElement_t elem1 = 0;
    err = POP(processor->stack, elem1);

    StackElement_t elem2 = 0;
    err = POP(processor->stack, elem2);

    if (elem2 == elem1)
        processor->counter = processor->code[processor->counter + 1];
    else
        processor->counter += 2;

    // fprintf(fileerr, TYPEELEM "\n", processor->code[processor->counter]);    
    return err;
}

int ProcessorJumpNE(Processor_t* processor)
{
    int err = 0;

    StackElement_t elem1 = 0;
    err = POP(processor->stack, elem1);

    StackElement_t elem2 = 0;
    err = POP(processor->stack, elem2);

    if (elem2 != elem1)
        processor->counter = processor->code[processor->counter + 1];
    else
        processor->counter += 2;

    // fprintf(fileerr, TYPEELEM "\n", processor->code[processor->counter]);    
    return err;
}

//------------------------------------------------------------------------------------------------------------------------------------

void Calculate(Processor_t* processor) {
    
    StackElement_t* arr          = processor->code;
    StackElement_t* arr_register = processor->registers;

    int i = 0;

    while (processor->code[processor->counter] != 0) {
            int i = 0;

            while (arr_command[i].command != processor->code[processor->counter]) {
                i++;
            }
            
            // printf("code = %d\n", arr_command[i].command);
            arr_command[i].func(processor);

            // int c = getchar();
        }
}