#include "mainproc.h"


int main() {
    Processor_t processor = {};
    ProcessorCtor(&processor); 
    
    CALCULATE(processor);

    ProcessorDtor(&processor);
}

void ProcessorCtor(Processor_t* processor) {
    INITSTACK(processor->stack, 10);

    processor->code = TextConvertToBite("bitecode.txt");

    for (int i = 0; i < 8; i++)
        processor->registers[0] = 0;
    
}

void ProcessorDtor(Processor_t* processor) 
{
    free(processor->code);
    DTOR(processor->stack);
}