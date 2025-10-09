#include "asm.h"

//2 542 3 2 7 1 4 6 3

//2 80 2 40 54

//union
//enum type

//PUSH 80 ;comment\n
//

Command_t arr_command[50] = {
                            "HLT"  , 4, HLT_G  , 
                            "PUSH" , 5, PUSH_G ,
                            "MUL"  , 4, MUL_G  , 
                            "SUB"  , 4, SUB_G  ,
                            "OUT"  , 4, OUT_G  ,
                            "DIV"  , 4, DIV_G  , 
                            "ADD"  , 4, ADD_G  ,  
                            "SQRT" , 5, SQRT_G , 
                            "IN"   , 3, IN_G   ,
                            "POPR" , 5, POPR_G , 
                            "PUSHR", 6, PUSHR_G,
                            "JB"   , 3, JB_G   ,
                            "JBE"  , 4, JBE_G  ,
                            "JA"   , 3, JA_G   ,
                            "JAE"  , 4, JAE_G  ,
                            "JE"   , 3, JE_G   ,
                            "JNE"  , 4, JNE_G  
};

void Compile(const char* commandfile, int* label) {
    
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

    while (1) {
        // if (*buffer == 0 && buffer[1] == 0)
        //     break;
            
        while (isspace(*buffer)) {
            buffer++;
        }

        StackElement_t elem = 0;        

        sscanf(buffer, "%s", cmdStr); //Проверка
        // fprintf(fileerr, "cmdStr = %s\n", cmdStr);
        
        if (cmdStr[0] == ':') 
        {
            puts(cmdStr); // printf
            int label_index = atoi(cmdStr + 1);
            label[label_index] = count_element;

            // printf("label[%d] = %d\n", label_index, count_element);

            buffer = strchr(buffer, '\n');
        }

        sscanf(buffer, "%s", cmdStr); //Проверка

        int i = 0;

        #ifdef DEBUG_ASSEMBLER
        printf("cmdStr = ");
        puts(cmdStr);
        #endif

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
        
        if (i >= JB_G && i <= JNE_G) {
            while (isspace(*buffer)) {
                buffer++;
            }

            char label_name[40] = ""; 
            sscanf(buffer, "%s", label_name);

            // printf("label_name = ");
            // puts(label_name);

            int label_index = 0;
            label_index = atoi(label_name + 1);

            printf("%d\n", label_index); // PRINTF DEBUG
            printf(TYPEELEM "\n", elem);
            printf("elem = ");
            PRINTELEM(label[label_index]);
            PUSH(stack, label[label_index]);

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
            // if (buffer[1] == '\0')
            //     break;
        } 

        buffer = strchr(buffer, '\n');

        if (buffer == NULL)
            break;
    }

    // PRINTSTACK(stack);

    free(struct_buffer.buff);
    free(cmdStr); 

    // открывать файл с байт-кодом и печатать его туда
    FILE* bitecode = fopen("bitecode.asm", "wb");
    fprintf(fileerr, "count_elem = %d\n", count_element);

    WriteBiteCodeFile(bitecode, stack.data, count_element);
    fclose(bitecode);

    free(stack.data);
    // return stack.data;
}

void WriteBiteCodeFile(FILE* bitecode, StackElement_t* arr, int count_element) {
    // for (int i = 0; i < count_element; i++) {
        // fprintf(bitecode, "%d ", arr[i]);
    // }
    fwrite(arr, count_element, sizeof(StackElement_t), bitecode);
}