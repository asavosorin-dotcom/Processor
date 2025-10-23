#include "mainproc.h"

#define RAM_SIZE 3000

FILE* fileerr = fopen("Logfile1.log", "w");
FILE* fileout = fopen("Fileout.txt", "w");

int main() {
    
    Processor_command_t* arr_command = (Processor_command_t* ) calloc(50, sizeof(Processor_command_t));
    Processor_Init_ArrCommand(arr_command);

    Processor_t processor = {};
    ProcessorCtor(&processor); 
    
    StackElement_t* point_code = processor.code;

    Processor(&processor, arr_command);

    processor.code = point_code;
    
    ProcessorDtor(&processor);
    fclose(fileerr);
    free(arr_command);
    printf(BOLD_GREEN "\nSUCCES!\n" RESET);
}

void ProcessorCtor(Processor_t* processor) 
{
    INITSTACK(processor->stack, 10);

    processor->code = TextConvertToBite("bytecode.bin");

    for (int i = 0; i < 10; i++)
        processor->registers[0] = 0;

    processor->counter = 0;

    INITSTACK(processor->ReturnStack, 10);
    processor->RAM_size = RAM_SIZE;
    processor->RAM = (int* ) calloc(processor->RAM_size, sizeof(int));
}

void ProcessorDtor(Processor_t* processor) 
{
    free(processor->code);
    free(processor->RAM);
    DTOR(processor->stack);
    DTOR(processor->ReturnStack);
}

StackElement_t* TextConvertToBite(const char* filename) 
{

    BufferBin struct_buffer = CreateBufferBinary(filename);

    StackElement_t* buffer = struct_buffer.buff;
    assert(buffer);

    return buffer;
}

void Processor_Init_ArrCommand(Processor_command_t* arr_command)
{
    ADD_COMMAND(arr_command, HLT_G  ,  0               ) 
    ADD_COMMAND(arr_command, PUSH_G ,  ProcessorPush   )
    ADD_COMMAND(arr_command, MUL_G  ,  ProcessorMul    )
    ADD_COMMAND(arr_command, SUB_G  ,  ProcessorSub    )
    ADD_COMMAND(arr_command, OUT_G  ,  ProcessorOut    )
    ADD_COMMAND(arr_command, DIV_G  ,  ProcessorDiv    )  
    ADD_COMMAND(arr_command, ADD_G  ,  ProcessorAdd    ) 
    ADD_COMMAND(arr_command, SQRT_G ,  ProcessorSqr    ) 
    ADD_COMMAND(arr_command, IN_G   ,  ProcessorIn     )
    ADD_COMMAND(arr_command, POPR_G ,  ProcessorPopr   )
    ADD_COMMAND(arr_command, PUSHR_G,  ProcessorPushr  )
    ADD_COMMAND(arr_command, JB_G   ,  ProcessorJump_B )
    ADD_COMMAND(arr_command, JBE_G  ,  ProcessorJump_BE)
    ADD_COMMAND(arr_command, JA_G   ,  ProcessorJump_A )
    ADD_COMMAND(arr_command, JAE_G  ,  ProcessorJump_AE)
    ADD_COMMAND(arr_command, JE_G   ,  ProcessorJump_E )
    ADD_COMMAND(arr_command, JNE_G  ,  ProcessorJump_NE)
    ADD_COMMAND(arr_command, J_G    ,  ProcessorJump   )
    ADD_COMMAND(arr_command, CALL_G ,  ProcessorCall   )
    ADD_COMMAND(arr_command, RET_G  ,  ProcessorRet    )
    ADD_COMMAND(arr_command, PUSHM_G,  ProcessorPushm  )
    ADD_COMMAND(arr_command, POPM_G ,  ProcessorPopm   )
    ADD_COMMAND(arr_command, DRAW_G ,  ProcessorDraw   )
    ADD_COMMAND(arr_command, REM_G  ,  ProcessorRemdiv )
}