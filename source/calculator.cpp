// #include "calculate.h"
#include "calculator.h"

// Считывание файла в буфер с переделыванием code.ASM в исполняемый байт-код
// Байт-код будет храниться в массиве, который нужно создать
// 

Processor_command_t arr_command[50] = { 
                            HLT_G  ,  0,
                            PUSH_G ,  ProcessorPush,
                            MUL_G  ,  ProcessorMul ,
                            SUB_G  ,  ProcessorSub ,
                            OUT_G  ,  ProcessorOut ,
                            DIV_G  ,  ProcessorDiv ,
                            ADD_G  ,  ProcessorAdd ,
                            SQRT_G ,  ProcessorSqr , 
                            IN_G   ,  ProcessorIn  ,
                            POPR_G ,  ProcessorPopr,
                            PUSHR_G,  ProcessorPushr
};

int ProcessorPush(Processor_t* processor) 
{
    int err = 0;
    
    // //printf("code = %d\n", *processor->code);

    processor->code++;



    StackElement_t elem = *processor->code;
    PUSH(processor->stack, elem);

    processor->code++;

    //printf("code = %d\n", *processor->code);

    return err;
}

int ProcessorOut(Processor_t* processor) 
{
    StackElement_t elem = *processor->code;
    int err = 0;
    err = POP(processor->stack, elem);
    (err != 0) ? printf(RED "Empty Stack\n" RESET) : PRINTELEM(elem)

    processor->code++;
    // fprintf(fileerr, "%d\n", *processor->code);

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

    processor->code++;

    return err;
}

int ProcessorSub(Processor_t* processor) 
{
    StackElement_t elem1 = 0;
    int err = POP(processor->stack, elem1);

    StackElement_t elem2 = 0;
    err |= POP(processor->stack, elem2);

    err |= PUSH(processor->stack, elem2 - elem1);

    processor->code++;

    return err;
}

int ProcessorMul(Processor_t* processor) 
{
    
    StackElement_t elem1 = 0;
    int err = POP(processor->stack, elem1);

    StackElement_t elem2 = 0;
    err |= POP(processor->stack, elem2);

    err |= PUSH(processor->stack, elem2 * elem1);

    processor->code++;

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

    processor->code++;

    return err;
}

int ProcessorSqr(Processor_t* processor) 
{    
    StackElement_t elem1 = 0;
    int err = POP(processor->stack, elem1);
    elem1 = (StackElement_t) floor(sqrt(elem1 * pow(10, 6))) / 1000;

    err |= PUSH(processor->stack, elem1);

    processor->code++;

    return err;
}

int ProcessorIn(Processor_t* processor) 
{
    int err = 0;
    
    printf(BOLD_BLUE "Enter value:\n" RESET);

    StackElement_t val = 0;
    scanf(TYPEELEM, &val);
    err = PUSH(processor->stack, val);

    processor->code++;

    return err;
}

int ProcessorPopr(Processor_t* processor) 
{
    int err = 0;
    
    StackElement_t val = 0;
    err = POP(processor->stack, val);
    // PRINTELEM(val);
    processor->code++;

    // printf("code in popr = %d\n", *processor->code);

    processor->registers[*processor->code - 1] = val;
    processor->code++;

    // printf("code after popr = %d\n", *processor->code);

    return err;
}

int ProcessorPushr(Processor_t* processor) 
{
    int err = 0;
    
    processor->code++;

    // printf(TYPEELEM"\n", arr_register[arr[i]].register_value);
    err = PUSH(processor->stack, processor->registers[*processor->code - 1]);

    processor->code++;

    // printf("code after pushr = %d\n", *processor->code);

    return err;
}

void Calculate(Processor_t* processor) {
    
    StackElement_t* arr          = processor->code;
    StackElement_t* arr_register = processor->registers;

    int i = 0;

    while (*processor->code != 0) {
            int i = 0;

            while (arr_command[i].command != *processor->code) {
                i++;
            }
            
            // printf("code = %d\n", arr_command[i].command);
            arr_command[i].func(processor);
        }
}