#include <stdio.h>

int main() {
    unsigned char push = 1;
    int num = 1026;

    unsigned char bytecode[5] = {1, 2, 4, 0, 0};

    // bytecode[0] = push;
    // *(int *)(bytecode + 1) = num;

    // for (int i = 0; i < 5; i++)
    //     printf("%d\n", bytecode[i]);

    printf("%d\n", bytecode[0]);
    printf("%d\n", *(int *)(bytecode + 1));


}