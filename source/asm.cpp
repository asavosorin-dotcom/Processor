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
                            "DRAW" , 5, DRAW_G ,
                            "REM"  , 4, REM_G
};

int num_command = 26;

void CompileCtor(const char* commandfile, Compile_t* compile_struct)
{
    Buffer struct_buffer = CreateBuffer(commandfile);
    INITSTACK(compile_struct->stack, 7);

    compile_struct->buffer = struct_buffer.buff;
    compile_struct->count_element = 0;
}

void CompileDtor(Compile_t* compile_struct)
{
    free(compile_struct->cmdStr);
    DTOR(compile_struct->stack);
}

void Assembler_Push        (Compile_t* compile_struct)
{
    int elem = 0;
    
    PRINT_DEBUG(BOLD_BLUE "-------------------------------------------------------------------------------------------------\n")
    PRINT_DEBUG("buffer_before_skip = %.10s\n", compile_struct->buffer)
    
    compile_struct->buffer = skip_space(compile_struct->buffer);
            
    ONDEBUGASM(printf("string = [%.10s] \n", compile_struct->buffer));

    if (sscanf(compile_struct->buffer, TYPEELEM, &elem) != 1) 
        printf(RED "\nError read arg in push\n" RESET);
    
    ONDEBUGASM(printf(BOLD_BLUE "elem in push = " TYPEELEM "\n", elem));
    PUSH(compile_struct->stack, elem)

    compile_struct->count_element++;

    PRINT_DEBUG("\n-------------------------------------------------------------------------------------------------\n" RESET)

}

int Assembler_Write_label (Assembler_t* assembler,  Compile_t* compile_struct)
{
    #ifdef DEBUG_ASSEMBLER
            printf("label = %s\n", compile_struct->cmdStr);
            printf("buffer[0] = %c, buffer[1] = %c\n", compile_struct->buffer[0], compile_struct->buffer[1]);
    #endif

    compile_struct->buffer++;

    #ifdef DEBUG_ASSEMBLER
        // printf("%d\n", sscanf(buffer, "%d", &assembler->label.->label_name));
        // label[label_index] = count_element;
    #endif

    if (sscanf(compile_struct->buffer, "%s", assembler->label[assembler->label_index].label_name ) != 1)
    {
        printf(BOLD_RED "Error reading label name\n");
        return ERR;
    }
     
    assembler->label[assembler->label_index].label_value = compile_struct->count_element; 

    #ifdef DEBUG_ASSEMBLER
        printf(BLUE "-----------------------------------------------------------------------\nSTART label\n\n");
        printf("label[%d] = %s %d\n",assembler->label_index, assembler->label[assembler->label_index].label_name, assembler->label[assembler->label_index].label_value);
        printf("\nEND label\n-----------------------------------------------------------------------\n\n" RESET);
    #endif

    assembler->label_index++;
    compile_struct->buffer = strchr(compile_struct->buffer, '\n');

    compile_struct->buffer = skip_space(compile_struct->buffer);

    ONDEBUGASM(printf("str_after_label = [%.20s]\n", compile_struct->buffer));

    return OK;
}

int Assembler_Search_Command (Assembler_t* assembler, Compile_t* compile_struct, int* i)
{    
    // #ifdef DEBUG_ASSEMBLER
    //     printf(BOLD_GREEN "----------------------------------------------------------------------------------------\nIn Search_Commnad\n");
    //     printf("i = %d\n", *i);
    //     printf("----------------------------------------------------------------------------------------\n" RESET);
    // #endif
    
    
    for (;strcmp(compile_struct->cmdStr, arr_command[*i].command_name) != 0; (*i)++) 
    {
        // ONDEBUGASM(printf(BOLD_GREEN "i = %d\n", *i));
        // PRINT_DEBUG("arr_command[%d] = %s\n", *i, arr_command[*i].command_name)

        if (*i == num_command - 1)
        {
            printf(BOLD_RED "\nUnknown command!!!\n\n" RESET);
            return ERR;
        }
    }

    return OK;    
}

int Assembler_Jump         (Assembler_t* assembler, Compile_t* compile_struct)

{
    compile_struct->buffer = skip_space(compile_struct->buffer);

    char jmp_arg[40] = ""; 
    sscanf(compile_struct->buffer, "%s", jmp_arg);

    char label_name[40] = "";

    if (jmp_arg[0] == ':')
        sscanf(compile_struct->buffer + 1, "%s", label_name);
    else
        return ERR;

    ONDEBUGASM(printf("%s\n", label_name)); 
    int i = 0;
    ONDEBUGASM(printf(RED "label_index = %d\n" RESET, assembler->label_index));

    if (assembler->label_count <= assembler->label_index)
        assembler->label_count = assembler->label_index;

    for (; i < assembler->label_count; i++)
    {
        if (strcmp(assembler->label[i].label_name, label_name) == 0)
            break;
    }

    #ifdef DEBUG_ASSEMBLER
        printf(MAGENTA"------------------------------------------------------------------\nJUMP\n\n");
        printf("index_in_label = %d\n", i);
        printf("elem = %d\n", assembler->label[i].label_value);
        printf("label_name = %s\n", assembler->label[i].label_name);
        printf("\nEND_OF_JUMP\n------------------------------------------------------------------\n"RESET);
    #endif

    PUSH(compile_struct->stack, assembler->label[i].label_value);
    compile_struct->count_element++;

    return OK;
}

void Assembler_Register_Arg (Compile_t* compile_struct)
{
    compile_struct->buffer = skip_space(compile_struct->buffer);

    char name[10] = ""; 
    sscanf(compile_struct->buffer, "%s", name);

    ONDEBUGASM(fprintf(fileerr, "register name[1] - A = %d\n", name[1] - 'A'));

    PUSH(compile_struct->stack, name[1] - 'A' + 1);

    compile_struct->buffer += 4;
    compile_struct->count_element++;
}

int Assembler_RAM (Compile_t* compile_struct)
{
    compile_struct->buffer = skip_space(compile_struct->buffer);

    char name[10] = ""; 
    sscanf(compile_struct->buffer, "%s", name);
    ONDEBUGASM(printf(BOLD_RED "name in popm = %.20s\n" RESET, compile_struct->buffer));

    if (name[0] !=  '[')
    {
        return ERR;
    }

    fprintf(fileerr, "register name[1] - A = %d\n", name[2] - 'A');
    PUSH(compile_struct->stack, name[2] - 'A' + 1);
    compile_struct->buffer += 6;

    compile_struct->count_element++;

    return OK;
}

char* skip_space(char* buffer)
{
    while (isspace(*buffer)) {
            buffer++;
        }

    return buffer;
}

void Compile(const char* commandfile, Assembler_t* assembler) 
{
    Compile_t compile_struct = {};
    CompileCtor(commandfile, &compile_struct);

    char* buf_for_free = compile_struct.buffer;

    compile_struct.buffer++;

//-------------------------------------------------------------------------------------------------------------------------------------
    compile_struct.cmdStr = (char* ) calloc(30, sizeof(char));
//-------------------------------------------------------------------------------------------------------------------------------------

    while (1) {
        compile_struct.buffer = skip_space(compile_struct.buffer);

        sscanf(compile_struct.buffer, "%s", compile_struct.cmdStr); //Проверка на scanf        
        ONDEBUGASM(fprintf(stdout, "%s:%d: compile_struct->cmdStr = %s\n", __FILE__, __LINE__, compile_struct.cmdStr));
        
        if (compile_struct.cmdStr[0] == ':') 
        {
            int err = Assembler_Write_label(assembler, &compile_struct);
            if (err == ERR)
            {
                printf(BOLD_RED "Error label name format\n" RESET);
                break;
            }
        }

        sscanf(compile_struct.buffer, "%s", compile_struct.cmdStr); //Проверка

        // ONDEBUGASM(fprintf(stdout, "\ncompile_struct.cmdStr_after_label = %s\n", compile_struct->cmdStr));

        int command_index = 0;
        int err = Assembler_Search_Command(assembler, &compile_struct, &command_index);
        
        compile_struct.buffer = skip_space(compile_struct.buffer);

        compile_struct.count_element++;

        // PRINT_DEBUG("\nbuffer_before_command = %.10s\n", compile_struct->buffer)

        #define $ printf(GREEN "%s:%d: stack@%p: data=[%p]\n" RESET, __FILE__, __LINE__, &compile_struct.stack, compile_struct.stack.data);

        compile_struct.buffer += arr_command[command_index].command_size;

        // PRINT_DEBUG("\nbuffer_after_command = %.10s\n", compile_struct->buffer)

        $

        PRINT_DEBUG("command_code = %d\n", arr_command[command_index].command_code)
        // PRINT_DEBUG(GREEN "before push[%p]\n" RESET, compile_struct->stack.data) 
        PUSH(compile_struct.stack, arr_command[command_index].command_code);
        // PRINT_DEBUG(GREEN "after push [%p]\n" RESET, compile_struct->stack.data) 

        $

        err = 0;

        if (command_index == PUSH_G) { // PUSH
            Assembler_Push(&compile_struct);
        }
        
        if (command_index >= JB_G && command_index <= CALL_G) {
            err = Assembler_Jump(assembler, &compile_struct);

            if (err)
            {
                printf(RED "Error Jump\n");
            }
        }

        else if (command_index == PUSHR_G || command_index == POPR_G) { // проверка RAX
            Assembler_Register_Arg(&compile_struct);
        }

        else if (command_index == PUSHM_G || command_index == POPM_G) { // проверка RAX
            err = Assembler_RAM(&compile_struct);

            if (err)
            {
                printf(RED "Error format pushm\n" RESET);
                break;
            }
        }

        $
        compile_struct.buffer = strchr(compile_struct.buffer, '\n');
        $

        if (compile_struct.buffer == NULL)
            break;
    }

    // открывать файл с байт-кодом и печатать его туда
    FILE* bitecode = fopen("bitecode.asm", "wb");
    fprintf(fileerr, "count_elem = %d\n", compile_struct.count_element);

    assembler->label_count = assembler->label_index;
    assembler->label_index = 0;

    WriteBiteCodeFile(bitecode, compile_struct.stack.data, compile_struct.count_element);
    
    free(buf_for_free);
    CompileDtor(&compile_struct);
    fclose(bitecode);

    // return stack.data;
}

void WriteBiteCodeFile(FILE* bitecode, StackElement_t* arr, size_t count_element) {
    // for (int i = 0; i < count_element; i++) {
        // fprintf(bitecode, "%d ", arr[i]);
    // }
    fwrite(arr, count_element, sizeof(StackElement_t), bitecode);
}