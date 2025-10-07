#include "mainasm.h"

FILE* fileerr = fopen("Logfile.log", "w");

int main() {
    ConvertToBite("commandfile123.txt");

    // for (int i = 0; arr[i] != 0; i++) {
    //     printf("%d ", arr[i]);
    // }

    // for (int i = 0; i < 7; i++) {
    //     printf("i = %d\n", i);
    //     printf("command_name = %s\n", arr_command[i].command_name);
    // }

    fclose(fileerr);
}