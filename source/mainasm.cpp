#include "mainasm.h"

FILE* fileerr = fopen("Logfile.log", "w");

int main() {
    int label[10] = {};

    for (int i = 0; i < 10; i++)
        label[i] = -1;
    
    Compile("commandfile.asm", label);
    Compile("commandfile.asm", label);

    // for (int i = 0; arr[i] != 0; i++) {
    //     printf("%d ", arr[i]);
    // }

    // for (int i = 0; i < 7; i++) {
    //     printf("i = %d\n", i);

    //     printf("command_name = %s\n", arr_command[i].command_name);
    // }

    fclose(fileerr);
    printf(BOLD_GREEN "SUCCES!\n" RESET);
}