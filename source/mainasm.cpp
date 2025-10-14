#include "mainasm.h"

FILE* fileerr = fopen("Logfile.log", "w");

int main() {
    
    Assembler_t assembler = {};
    AssemblerCtor(&assembler);

    Label_t labels[10] = {0};

    for (int i = 0; i < 10; i++) // иницализация массива labels
    {
        labels[i] = {-1, -1};
    }  

    char* commandfile = "commandfiletest.asm";
    Compile(commandfile, &assembler);
    Compile(commandfile, &assembler);

    // for (int i = 0; arr[i] != 0; i++) {
    //     printf("%d ", arr[i]);
    // }

    // for (int i = 0; i < 7; i++) {
    //     printf("i = %d\n", i);

    //     printf("command_name = %s\n", arr_command[i].command_name);
    // }

    fclose(fileerr);
    printf(BOLD_GREEN "SUCCES!\n" RESET);

    return 0;
}

void AssemblerCtor(Assembler_t* assembler) 
{
    for (int i = 0; i < 10; i++) // иницализация массива labels
    {
        assembler->label[i] = {-1, -1};
    }
    
    assembler->label_index = 0;
}