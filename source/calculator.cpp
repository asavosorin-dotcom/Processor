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

void Calculate(Stack_t* stk1, StackElement_t* arr) {
    
    StackElement_t elem = 0;
    int i = 0;

    while (1) {
            
            if (arr[i] == 1) { 
                i++;
                elem = arr[i];
                PUSH(*stk1, elem);
                i++;
            }

            else if (arr[i] == 4) {
                int err = POP(*stk1, elem);
                (err != 0) ? printf("Empty Stack\n") : PRINTELEM(elem)

                i++;
            }

            else if (arr[i] == 6) {
                ADD(*stk1);

                i++;
            }

            else if (arr[i] == 3) {
                SUB(*stk1);

                i++;
            }

            else if (arr[i] == 5) {
                DIV(*stk1);

                i++;
            }

            else if (arr[i] == 2) {
                MUL(*stk1);

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