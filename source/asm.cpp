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
                            "JNE"  , 4, JNE_G  ,
                            "J"    , 2, J_G    ,
                            "CALL" , 5, CALL_G ,
                            "RET"  , 4, RET_G  ,
                            "PUSHM", 6, PUSHM_G,
                            "POPM" , 5, POPM_G ,
                            "DRAW" , 5, DRAW_G
};

int num_command = 25;

void Compile(const char* commandfile, Assembler_t* assembler) 
{
    
    Buffer struct_buffer = CreateBuffer(commandfile);
    char*  buffer        = struct_buffer.buff;

    // OutPutBuf(buffer, stdout, struct_buffer.buff_size + 2);

    buffer += 1;

    // printf("size = %d\n", struct_buffer.buff_size);

//-------------------------------------------------------------------------------------------------------------------------------------
    char* cmdStr = (char* ) calloc(30, sizeof(char));
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
        
        //PUSH 80
        fprintf(stdout, "cmdStr = %s\n", cmdStr);
        
        if (cmdStr[0] == ':') 
        {
            printf("label = %s\n", cmdStr);
            printf("buffer[0] = %c, buffer[1] = %c\n", buffer[0], buffer[1]);
            buffer++;
            // printf("%d\n", sscanf(buffer, "%d", &assembler->label.->label_name));
            // label[label_index] = count_element;
            sscanf(buffer, "%s", &assembler->label[assembler->label_index].label_name); //Проверку
            assembler->label[assembler->label_index].label_value = count_element; // переделать под массив структур меток, пока под одну
            // придумать как индексировать этот массив

            printf(BLUE "-----------------------------------------------------------------------\nSTART label\n\n");

            printf("label[%d] = %s %d\n",assembler->label_index, assembler->label[assembler->label_index].label_name, assembler->label[assembler->label_index].label_value);
            
            printf("\nEND label\n-----------------------------------------------------------------------\n\n" RESET);

            assembler->label_index++;
            buffer = strchr(buffer, '\n');

            while (isspace(*buffer))
                buffer++;

            printf("str_after_label = [%.20s]\n", buffer);
        }

        sscanf(buffer, "%s", cmdStr); //Проверка

        int i = 0;

        #ifdef DEBUG_ASSEMBLER
        printf("cmdStr = ");
        puts(cmdStr);
        #endif

        while (isspace(*buffer))
            buffer++;

        for (;strcmp(cmdStr, arr_command[i].command_name) != 0; i++) 
        {
            if (i == num_command - 1)
            {
                printf(BOLD_RED "\nUnknown command!!!\n\n" RESET);
                break;
            }
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
            
            // printf("string = [%.10s] \n", buffer);

            if (sscanf(buffer, TYPEELEM, &elem) != 1) //Проверки
                printf(RED "\nError read arg in push\n" RESET);
            
            printf("elem in push = " TYPEELEM "\n", elem);
            PUSH(stack, elem);

            count_element++;
        }
        
        if (i >= JB_G && i <= CALL_G) {
            while (isspace(*buffer)) {
                buffer++;
            }

            char jmp_arg[40] = ""; 
            sscanf(buffer, "%s", jmp_arg);

            // printf("label_name = ");
            // puts(label_name);
            char label_name[40] = "";

            if (jmp_arg[0] == ':')
                sscanf(buffer + 1, "%s", &label_name);

            // for (int i = 0; i < 10; i++)
            //     if (assembler->label[i])

            printf("%s\n", label_name); // PRINTF DEBUG

            int i = 0;

            printf(RED"label_index = %d\n"RESET, assembler->label_index);

            for (; i < assembler->label_index; i++)
            {
                if (strcmp(assembler->label[i].label_name, label_name) == 0)
                    break;
            }

            // printf(TYPEELEM "\n", elem);
            printf(MAGENTA"------------------------------------------------------------------\nJUMP\n\n");
            printf("index_in_label = %d\n", i);
            printf("elem = %d\n", assembler->label[i].label_value);
            printf("label_name = %s\n", assembler->label[i].label_name);
            PUSH(stack, assembler->label[i].label_value);
            printf("\nEND_OF_JUMP\n------------------------------------------------------------------\n"RESET);

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

        else if (i == PUSHM_G || i == POPM_G) { // проверка RAX
            while (isspace(*buffer)) {
                buffer++;
            }

            char name[10] = ""; 
            sscanf(buffer, "%s", name);

            if (name[0] !=  '[')
            {
                printf(RED "Error format pushm\n" RESET);
                break;
            }

            fprintf(fileerr, "register name[1] - A = %d\n", name[2] - 'A');
            PUSH(stack, name[2] - 'A' + 1);
            buffer += 6;

            count_element++;

        }

        // printf("*buffer = %c\n", buffer[-2]);
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

    // assembler->label_index = 0;

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