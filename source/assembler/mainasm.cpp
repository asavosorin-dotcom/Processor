#include "mainasm.h"

FILE* fileerr = fopen("Logfile.log", "w");

int main(int argc, char* argv[]) {
    
    Assembler_t assembler = {};
    AssemblerCtor(&assembler);

    Command_t* arr_command = (Command_t* ) calloc(50, sizeof(Command_t));
    Assembler_Init_arr_command(arr_command);

    char* commandfile = argv[1];
    Compile(commandfile, &assembler, arr_command);
    Compile(commandfile, &assembler, arr_command);

    // for (int i = 0; arr[i] != 0; i++) {
    //     printf("%d ", arr[i]);.
    // }

    // for (int i = 0; i < 7; i++) {
    //     printf("i = %d\n", i);

    //     printf("command_name = %s\n", arr_command[i].command_name);
    // }

    fclose(fileerr);
    printf(BOLD_GREEN "\nSUCCES!\n" RESET);
    free(arr_command);

    return 0;
}

void AssemblerCtor(Assembler_t* assembler) 
{
    for (int i = 0; i < LABEL_SIZE; i++) // иницализация массива labels
    {
        assembler->label[i] = {"", -1};
    }
    
    assembler->label_index = 0;
    assembler->label_count = 0;
}

void Assembler_Init_arr_command(Command_t* arr_command)
{
                            ADD_ARR_COMMANDS(arr_command, "HLT"  , 4, HLT_G  ) 
                            ADD_ARR_COMMANDS(arr_command, "PUSH" , 5, PUSH_G )
                            ADD_ARR_COMMANDS(arr_command, "MUL"  , 4, MUL_G  ) 
                            ADD_ARR_COMMANDS(arr_command, "SUB"  , 4, SUB_G  )
                            ADD_ARR_COMMANDS(arr_command, "OUT"  , 4, OUT_G  )
                            ADD_ARR_COMMANDS(arr_command, "DIV"  , 4, DIV_G  ) 
                            ADD_ARR_COMMANDS(arr_command, "ADD"  , 4, ADD_G  )  
                            ADD_ARR_COMMANDS(arr_command, "SQRT" , 5, SQRT_G ) 
                            ADD_ARR_COMMANDS(arr_command, "IN"   , 3, IN_G   )
                            ADD_ARR_COMMANDS(arr_command, "POPR" , 5, POPR_G ) 
                            ADD_ARR_COMMANDS(arr_command, "PUSHR", 6, PUSHR_G)
                            ADD_ARR_COMMANDS(arr_command, "JB"   , 3, JB_G   )
                            ADD_ARR_COMMANDS(arr_command, "JBE"  , 4, JBE_G  )
                            ADD_ARR_COMMANDS(arr_command, "JA"   , 3, JA_G   )
                            ADD_ARR_COMMANDS(arr_command, "JAE"  , 4, JAE_G  )
                            ADD_ARR_COMMANDS(arr_command, "JE"   , 3, JE_G   )
                            ADD_ARR_COMMANDS(arr_command, "JNE"  , 4, JNE_G  )
                            ADD_ARR_COMMANDS(arr_command, "J"    , 2, J_G    )
                            ADD_ARR_COMMANDS(arr_command, "CALL" , 5, CALL_G )
                            ADD_ARR_COMMANDS(arr_command, "RET"  , 4, RET_G  )
                            ADD_ARR_COMMANDS(arr_command, "PUSHM", 6, PUSHM_G)
                            ADD_ARR_COMMANDS(arr_command, "POPM" , 5, POPM_G )
                            ADD_ARR_COMMANDS(arr_command, "DRAW" , 5, DRAW_G )
                            ADD_ARR_COMMANDS(arr_command, "REM"  , 4, REM_G  )
};
