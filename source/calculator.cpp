// #include "calculate.h"
#include "calculator.h"

// Считывание файла в буфер с переделыванием code.ASM в исполняемый байт-код
// Байт-код будет храниться в массиве, который нужно создать
// 

int add(Stack_t* stk) {
    StackElement_t elem1 = 0;
    int err = POP(*stk, elem1);

    StackElement_t elem2 = 0;
    err |= POP(*stk, elem2);

    err |= PUSH(*stk, elem1 + elem2);

    return err;
}

int sub(Stack_t* stk) {
    StackElement_t elem1 = 0;
    int err = POP(*stk, elem1);

    StackElement_t elem2 = 0;
    err |= POP(*stk, elem2);

    err |= PUSH(*stk, elem2 - elem1);

    return err;
}

int mul(Stack_t* stk) {
    StackElement_t elem1 = 0;
    int err = POP(*stk, elem1);

    StackElement_t elem2 = 0;
    err |= POP(*stk, elem2);

    err |= PUSH(*stk, elem2 * elem1);

    return err;
}

int div(Stack_t* stk) {
    StackElement_t elem1 = 0;
    int err = POP(*stk, elem1);

    StackElement_t elem2 = 0;
    err |= POP(*stk, elem2);

    err |= PUSH(*stk, elem2 / elem1);

    return err;
}

int sqr(Stack_t* stk) {
    StackElement_t elem1 = 0;
    int err = POP(*stk, elem1);
    elem1 = (StackElement_t) floor(sqrt(elem1 * pow(10, 6))) / 1000;

    err |= PUSH(*stk, elem1);

    return err;
}

void Calculate(Processor_t* processor) {
    
    StackElement_t* arr          = processor->code;
    Stack_t         stk1         = processor->stack;
    StackElement_t* arr_register = processor->registers;

    StackElement_t elem = 0;
    int i = 0;

    while (1) {
            
            if (arr[i] == 1) 
            { 
                i++;
                elem = arr[i];
                PUSH(stk1, elem);
                i++;
            }

            else if (arr[i] == 4) 
            {
                int err = POP(stk1, elem);
                (err != 0) ? printf(RED "Empty Stack\n" RESET) : PRINTELEM(elem)

                i++;
            }

            else if (arr[i] == 6) 
            {
                ADD(stk1);

                i++;
            }

            else if (arr[i] == 3) 
            {
                SUB(stk1);

                i++;
            }

            else if (arr[i] == 5) 
            {
                DIV(stk1);

                i++;
            }

            else if (arr[i] == 2) 
            {
                MUL(stk1);

                i++;
            } 

            else if (arr[i] == 7)
            {
                SQRT(stk1);

                i++;
            }
            
            else if (arr[i] == 8)
            {
                printf(BOLD_BLUE "Enter value:\n" RESET);
                StackElement_t val = 0;
                scanf(TYPEELEM, &val);
                PUSH(stk1, val);

                i++;
            }

            else if (arr[i] == POPR_G) 
            {
                StackElement_t val = 0;
                POP(stk1, val);
                i++;
                arr_register[arr[i]] = val;
                i++;
            }

            else if (arr[i] == PUSHR_G) 
            {
                i++;
                // printf(TYPEELEM"\n", arr_register[arr[i]].register_value);
                PUSH(stk1, arr_register[arr[i]]);
                i++;
            }

            // else if (arr[i] == 4) {
            //     SQRT(*stk1);
            // }

            // else if (strcmp("PRINT", command) == 0) {
            //     PRINTSTACK(*stk1);
            // }

            else if (arr[i] == 0) {
                break;
            }

            else {
                printf("Enter correct command\n");
            }
        }
}