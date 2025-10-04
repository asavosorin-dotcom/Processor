#include "asm.h"

//2 542 3 2 7 1 4 6 3

//2 80 2 40 5

// enum and arr of struct



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
        // printf("%s\n", cmdStr);

        if (strcmp(cmdStr, "PUSH") == 0) {
            buffer += 5;
            PUSH(stack, 1);

            while (isspace(*buffer)) {
                buffer++;
            }

            sscanf(buffer, ELEMTYPE, &elem);
            // printf(ELEMTYPE "\n", elem);
            PUSH(stack, elem);
            
            buffer = strchr(buffer, '\n');
        }

        else if (strcmp(cmdStr, "MUL") == 0) {
            buffer += 4;
            PUSH(stack, 2);
        }

        else if (strcmp(cmdStr, "SUB") == 0) {
            buffer += 4;
            PUSH(stack, 3);
        }

        else if (strcmp(cmdStr, "OUT") == 0) {
            buffer += 4;
            PUSH(stack, 4);
        }

        else if (strcmp(cmdStr, "DIV") == 0) {
            buffer += 4;
            PUSH(stack, 5);
        }

        else if (strcmp(cmdStr, "ADD") == 0) {
            buffer += 4;
            PUSH(stack, 6);
        }

        else if (strcmp(cmdStr, "HLT") == 0) {
            // buffer += 4;
            PUSH(stack, 0);
            break;
        }

        // while (isspace(*buffer)) {
        //     buffer++;}
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
        fprintf(bitecode,"%d ", *arr);
        arr++;
    }

    fprintf(bitecode,"%d ", *arr);
}