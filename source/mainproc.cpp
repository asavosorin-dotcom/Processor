#include "mainproc.h"

FILE* fileerr = fopen("Logfile1.log", "w");

int main() {
    // fprintf(fileerr, "DKSAVNOADKSNV;LKASDNV");
    
    Processor_t processor = {};
    ProcessorCtor(&processor); 
    
    StackElement_t* point_code = processor.code;

    CALCULATE(processor);

    processor.code = point_code;
    
    ProcessorDtor(&processor);
    fclose(fileerr);
    printf(BOLD_GREEN "SUCCES!\n" RESET);
}

void ProcessorCtor(Processor_t* processor) {
    INITSTACK(processor->stack, 10);

    processor->code = TextConvertToBite("bitecode.asm");

    for (int i = 0; i < 8; i++)
        processor->registers[0] = 0;

    processor->counter = 0;

    INITSTACK(processor->ReturnStack, 10);

    processor->RAM = (int* ) calloc(100, sizeof(int));
}

void ProcessorDtor(Processor_t* processor) 
{
    free(processor->code);
    free(processor->RAM);
    DTOR(processor->stack);
    DTOR(processor->ReturnStack);
}