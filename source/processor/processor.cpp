#include "processor.h"

#define DRAW_STRING 51

// количество

void Processor (Processor_t* processor, Processor_command_t* arr_command) 
{
    
    StackElement_t* arr          = processor->code;
    StackElement_t* arr_register = processor->registers;

    int err = 0;
    ONDEBUGPROC(int command_counter = 0;) 
    while (processor->code[processor->counter] != 0) {
            #ifdef DEBUG
            printf(YELLOW "adress = %d\n" RESET, processor->counter);
            #endif

            err = arr_command[processor->code[processor->counter]].func(processor);
            if (err) break;

            #ifdef DEBUG
            printf("[%d]", command_counter);
            PRINTSTACK(processor->stack);
            PrintArr(processor->RAM, 100);
            int c = getchar();
            command_counter++;
            #endif

        }
}

void PrintArr(int* arr, int number_of_elem) // Спросить у Сани как сделать универсальный
{
    // printf(MAGENTA"-----------------------------------------------------------\n\nRAM");
    printf(MAGENTA);
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n"RESET);
    // printf("\n\n-----------------------------------------------------------\n"RESET);
}

int ProcessorPush  (Processor_t* processor) 
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

int ProcessorOut   (Processor_t* processor) 
{
    assert(processor);
    
    StackElement_t elem = processor->code[processor->counter];

    int err = 0;
    err = POP(processor->stack, elem);
    (err != 0) ? printf(RED "Empty Stack\n" RESET) : PRINTELEM(elem)

    processor->counter++;
    // fprintf(fileerr, "%d\n", processor->code[processor->counter]);

    // PRINTSTACK(processor->stack);
    return err;
}
 
//--------------------------------------------BASE---OPERATION----------------------------------------------------------------------
#define IMPL_BASE_OP(name, op) int Processor##name   (Processor_t* processor) \
{                                                                         \
    assert(processor);                                                    \
                                                                          \
    StackElement_t elem1 = 0;                                             \
    StackElement_t elem2 = 0;                                             \
                                                                          \
    int err = POP(processor->stack, elem1);                               \
    err |= POP(processor->stack, elem2);                                  \
                                                                          \
    err |= PUSH(processor->stack, elem2 op elem1);                        \
                                                                          \
    processor->counter++;                                                 \
                                                                          \
    return err;                                                           \
}
//----------------------------------------------------------------------------------------------------------------------------------

int ProcessorDiv   (Processor_t* processor) 
{                                                                         
    assert(processor);                                                    
                                                                          
    StackElement_t elem1 = 0;                                             
    StackElement_t elem2 = 0;                                             
                                                                          
    int err = POP(processor->stack, elem1);                               
    err |= POP(processor->stack, elem2);                                  
                                    
    if (elem1 == 0)
    {
        printf(RED "Division on 0\n" RESET);
        return ERR;
    }

    err |= PUSH(processor->stack, elem2 / elem1);                            
    processor->counter++;                                                 
                                                                          
                                                                          
    return err;                                                           
}

int ProcessorRemdiv   (Processor_t* processor) 
{                                                                         
    assert(processor);                                                    
                                                                          
    StackElement_t elem1 = 0;                                             
    StackElement_t elem2 = 0;                                             
                                                                          
    int err = POP(processor->stack, elem1);                               
    err |= POP(processor->stack, elem2);                                  
                                    
    if (elem1 == 0)
    {
        printf(RED "Division on 0\n" RESET);
        return ERR;
    }

    err |= PUSH(processor->stack, elem2 % elem1);                            
    processor->counter++;                                                 
                                                                          
                                                                          
    return err;                                                           
}

IMPL_BASE_OP(Add,    +)
IMPL_BASE_OP(Sub,    -)
IMPL_BASE_OP(Mul,    *) // 3 параметр, подставляющий if 

int ProcessorSqr   (Processor_t* processor) 
{    
    assert(processor);
    
    StackElement_t elem1 = 0;

    int err = POP(processor->stack, elem1);

    elem1 = (StackElement_t) floor(sqrt(elem1 * pow(10, 6))) / 1000;

    err |= PUSH(processor->stack, elem1);

    processor->counter++;

    return err;
}

int ProcessorIn    (Processor_t* processor) 
{
    assert(processor);
    
    int err = 0;
    
    printf(BOLD_BLUE "Enter value:\n" RESET);

    StackElement_t val = 0;
    scanf(TYPEELEM, &val);
    err = PUSH(processor->stack, val);

    processor->counter++;

    return err;
}

int ProcessorPopr  (Processor_t* processor) 
{
    assert(processor);
    
    int err = 0;
    
    StackElement_t val = 0;
    err = POP(processor->stack, val);
    // PRINTELEM(val);
    processor->counter++;

    ONDEBUGPROC(printf("code in popr = %d\n", processor->code[processor->counter]));

    processor->registers[processor->code[processor->counter] - 1] = val;
    processor->counter++;

    // printf("code after popr = %d\n", processor->code[processor->counter]);

    return err;
}

int ProcessorPushr (Processor_t* processor) 
{
    assert(processor);

    int err = 0;
    
    processor->counter++;

    // printf(TYPEELEM"\n", arr_register[arr[i]].register_value);
    err = PUSH(processor->stack, processor->registers[processor->code[processor->counter] - 1]);

    processor->counter++;

    // printf("code after pushr = %d\n", processor->code[processor->counter]);

    return err;
}

int ProcessorCall  (Processor_t* processor) 
{    
    int err = 0;
    
    PUSH(processor->ReturnStack, processor->counter + 2);
    ONDEBUGPROC(printf(MAGENTA"\nadress_call = %d\n"RESET, processor->counter + 2));
    ProcessorJump (processor);

    return err;
}

int ProcessorRet   (Processor_t* processor)
{
    int err = 0; 
    
    StackElement_t adress = 0;
    err = POP(processor->ReturnStack, adress);
    processor->counter = adress;

    ONDEBUGPROC(printf(BLUE "return adress = %d\n" RESET, adress));

    return err;
}

int ProcessorPushm (Processor_t* processor)
{
    int err = 0;

    int val = 0;
    ProcessorPushr(processor);
    POP(processor->stack, val);

    err = PUSH(processor->stack, processor->RAM[val]);

    return err;
}

int ProcessorPopm  (Processor_t* processor) 
{
    int err = 0;

    int val = 0;
    ProcessorPushr(processor);
    POP(processor->stack, val);

    ONDEBUGPROC(printf(YELLOW"\nPOPM\nval = %d\n\n"RESET, val));

    POP(processor->stack, processor->RAM[val]);

    return err;
}

//--------------------------------------------------------------JUMP-----------------------------------------------------------------
#define IMPL_JUMP(name, op_comparison) int ProcessorJump_##name(Processor_t* processor) \
{                                                                                       \
    assert(processor);                                                                  \
    int err = 0;                                                                        \
                                                                                        \
    StackElement_t elem1 = 0;                                                           \
    err = POP(processor->stack, elem1);                                                 \
                                                                                        \
    StackElement_t elem2 = 0;                                                           \
    err = POP(processor->stack, elem2);                                                 \
                                                                                        \
    if (elem2 op_comparison elem1)                                                      \
        processor->counter = processor->code[processor->counter + 1];                   \
    else                                                                                \
        processor->counter += 2;                                                        \
                                                                                        \
    return err;                                                                         \
}

IMPL_JUMP(B , < )
IMPL_JUMP(BE, <=)
IMPL_JUMP(A , > )
IMPL_JUMP(AE, >=)
IMPL_JUMP(E , ==)
IMPL_JUMP(NE, !=)

int ProcessorJump (Processor_t* processor) 
{
    assert(processor);                                                                  
    int err = 0;                                                                        
                                                                                        
    processor->counter = processor->code[processor->counter + 1];                   
    
    return err;
}
//------------------------------------------------------------------------------------------------------------------------------------
                                 
int ProcessorDraw (Processor_t* processor)
{
    // txCreateWindow(1000, 1000);
    
    int err = 0;
    
    for (int i = 0; i < processor->RAM_size; i++)
    {
        if (processor->RAM[i] == '*') fprintf(stdout, BOLD_RED "%c " RESET, processor->RAM[i]);
        else                          fprintf(stdout, "%c ", processor->RAM[i]);

        // printf("%d\n", i);

        if ((i + 1) % DRAW_STRING == 0) fprintf(stdout, "\n");
    }

    processor->counter++;
    return err;
}
