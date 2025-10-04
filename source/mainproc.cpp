#include "mainproc.h"


int main() {
    Stack_t stk1 = {};
    INITSTACK(stk1, 10);

    StackElement_t* arr = TextConvertToBite("bitecode.txt");
    CALCULATE(stk1, arr);

    free(arr);
    DTOR(stk1);
}