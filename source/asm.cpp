#include "asm.h"

//2 542 3 2 7 1 4 6 3

//2 80 2 40 5

// enum and arr of struct

Command_t arr_command[8] = {
                            "HLT",  4, HLT_G ,
                            "PUSH", 5, PUSH_G,
                            "MUL",  4, MUL_G ,
                            "SUB",  4, SUB_G ,
                            "OUT",  4, OUT_G ,
                            "DIV",  4, DIV_G ,
                            "ADD",  4, ADD_G , 
                            "SQRT", 5, SQRT_G
};

void ConvertToBite(const char* commandfile) {
    
    Buffer struct_buffer = CreateBuffer(commandfile);
    char* buffer = struct_buffer.buff;
    OutPutBuf(buffer, fileerr, struct_buffer.buff_size + 2);

    buffer += 1;

    // printf("size = %d\n", struct_buffer.buff_size);

//-------------------------------------------------------------------------------------------------------------------------------------
    char* cmdStr = (char* ) calloc(10, sizeof(char));
//-------------------------------------------------------------------------------------------------------------------------------------


    // OutPutBuf(buffer, stdout, struct_buffer.buff_size + 1);
    Stack_t stack = {};
    INITSTACK(stack, 7);

    // StackDump(&stack, 1024);

    while (*buffer != '\0') {
        
        while (isspace(*buffer)) {
            buffer++;}

        StackElement_t elem = 0;        

        sscanf(buffer, "%s", cmdStr);
        // fprintf(fileerr, "cmdStr = %s\n", cmdStr);
        
        int i = 0;

        while (strcmp(cmdStr, arr_command[i].command_name) != 0) {
            // fprintf(fileerr, "i = %d\n", i);
            i++;
        }
            
        // fprintf(fileerr, "strcmp = %d\n", strcmp(cmdStr, arr_command[i].command_name));
        // fprintf(fileerr, "arr_command = %s\n\n", arr_command[i].command_name);
        

        buffer += arr_command[i].command_size;
        PUSH(stack, arr_command[i].command_code);

        if (i == 1) { // PUSH
            while (isspace(*buffer)) {
                buffer++;
            }
            
            sscanf(buffer, ELEMTYPE, &elem);
            // printf(ELEMTYPE "\n", elem);
            PUSH(stack, elem);

        } else if (i == 0) { // HLT
            break;
        } 

        buffer = strchr(buffer, '\n');

    }

    // PRINTSTACK(stack);

    free(struct_buffer.buff);
    free(cmdStr); 

    // открывать файл с байт-кодом и печатать его туда
    FILE* bitecode = fopen("bitecode.txt", "w");
    WriteBiteCodeFile(bitecode, stack.data);
    fclose(bitecode);

    free(stack.data);
    // return stack.data;
}

void WriteBiteCodeFile(FILE* bitecode, StackElement_t* arr) {
    while (*arr != 0) {
        fprintf(bitecode, "%d ", *arr);
        arr++;
    }

    fprintf(bitecode, "%d ", *arr);
}