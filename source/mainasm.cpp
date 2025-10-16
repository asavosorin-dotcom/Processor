#include "mainasm.h"

FILE* fileerr = fopen("Logfile.log", "w");

int main(int argc, char* argv[]) {
    
    Assembler_t assembler = {};
    AssemblerCtor(&assembler);

    char* commandfile = argv[1];
    Compile(commandfile, &assembler);
    Compile(commandfile, &assembler);

    // for (int i = 0; arr[i] != 0; i++) {
    //     printf("%d ", arr[i]);.
    // }

    // for (int i = 0; i < 7; i++) {
    //     printf("i = %d\n", i);

    //     printf("command_name = %s\n", arr_command[i].command_name);
    // }

    fclose(fileerr);
    printf(BOLD_GREEN "\nSUCCES!\n" RESET);

    return 0;
}

void AssemblerCtor(Assembler_t* assembler) 
{
    for (int i = 0; i < 10; i++) // иницализация массива labels
    {
        assembler->label[i] = {"", -1};
    }
    
    assembler->label_index = 0;
}