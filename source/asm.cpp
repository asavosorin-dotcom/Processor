#include "asm.h"

//2 542 3 2 7 1 4 6 3

//2 80 2 40 5

extern Command_t arr_command[50];

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

    int count_element = 0;

    while (*buffer != '\0') {
        
        while (isspace(*buffer)) {
            buffer++;
        }

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
        
        count_element++;

        buffer += arr_command[i].command_size;
        PUSH(stack, arr_command[i].command_code);

        if (i == PUSH_G) { // PUSH
            while (isspace(*buffer)) {
                buffer++;
            }
            
            sscanf(buffer, TYPEELEM, &elem);
            // printf(ELEMTYPE "\n", elem);
            PUSH(stack, elem);

            count_element++;
        }
        
        else if (i == PUSHR_G || i == POPR_G) { // проверка RAX
            while (isspace(*buffer)) {
                buffer++;
            }

            char name[10] = ""; 
            sscanf(buffer, "%s", name);
            fprintf(fileerr, "register name[1] - A = %d\n", name[1] - 'A');
            PUSH(stack, name[1] - 'A' + 1);
            buffer += 4;

            count_element++;

        } else if (i == HLT_G) { // HLT
            break;
        } 

        buffer = strchr(buffer, '\n');

    }

    // PRINTSTACK(stack);

    free(struct_buffer.buff);
    free(cmdStr); 

    // открывать файл с байт-кодом и печатать его туда
    FILE* bitecode = fopen("bitecode.txt", "w");
    fprintf(fileerr, "count_elem = %d\n", count_element);

    WriteBiteCodeFile(bitecode, stack.data, count_element);
    fclose(bitecode);

    free(stack.data);
    // return stack.data;
}

void WriteBiteCodeFile(FILE* bitecode, StackElement_t* arr, int count_element) {
    for (int i = 0; i < count_element; i++) {
        fprintf(bitecode, "%d ", arr[i]);
    }
}