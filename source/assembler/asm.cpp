#include "asm.h"

//2 542 3 2 7 1 4 6 3

//2 80 2 40 54

//union
//enum type

//PUSH 80 ;comment\n
// перенести все комманды

int num_command = 30;

void Compile(const char* commandfile, Assembler_t* assembler, Command_t* arr_command) 
{
    Compile_t compile_struct = {};
    CompileCtor(commandfile, &compile_struct);

    char* buf_for_free = compile_struct.buffer;

    compile_struct.buffer++;


    int err = 0;

    while (1) {
        compile_struct.buffer = skip_space(compile_struct.buffer);

        sscanf(compile_struct.buffer, "%s", compile_struct.cmdStr); //Проверка на scanf        
        // ONDEBUGASM(fprintf(stdout, "%s:%d: compile_struct->cmdStr = %s\n", __FILE__, __LINE__, compile_struct.cmdStr));
        
        if (compile_struct.cmdStr[0] == ':') 
        {
            err = Assembler_Write_label(assembler, &compile_struct);
            BREAK
        }

        int command_index = 0;
        err = Assembler_Search_Command(assembler, &compile_struct, &command_index, arr_command);
        
        BREAK

        compile_struct.buffer += arr_command[command_index].command_size;

        PRINT_DEBUG(BOLD_BLUE, "\ncommand_name = [%s]\n", arr_command[command_index].command_name);
        PRINT_DEBUG(MAGENTA,"\ncommand_hash = [%zu]\n", arr_command[command_index].command_hash);
        PRINT_DEBUG(GREEN,  "command_code = [%d]\n\n", arr_command[command_index].command_code);
        PUSH(compile_struct.stack, arr_command[command_index].command_code);
        
        err = Assembler_get_arg(assembler, &compile_struct, command_index);

        BREAK

        compile_struct.buffer = strchr(compile_struct.buffer, '\n');
        
        if (compile_struct.buffer == NULL)
            break;

        // int c = getchar();
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

void CompileCtor(const char* commandfile, Compile_t* compile_struct)
{
    Buffer struct_buffer = CreateBuffer(commandfile);
    INITSTACK(compile_struct->stack, 7);

    compile_struct->buffer = struct_buffer.buff;
    compile_struct->count_element = 0;
    compile_struct->cmdStr = (char* ) calloc(30, sizeof(char));
}

void CompileDtor(Compile_t* compile_struct)
{
    free(compile_struct->cmdStr);
    DTOR(compile_struct->stack);
}

int Assembler_Write_label    (Assembler_t* assembler,  Compile_t* compile_struct)
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

int Assembler_Search_Command (Assembler_t* assembler, Compile_t* compile_struct, int* i, Command_t* arr_command)
{    
    #ifdef DEBUG_ASSEMBLER
        printf(BOLD_GREEN "----------------------------------------------------------------------------------------\nIn Search_Commnad\n");
        printf("i = %d\n", *i);
        printf("----------------------------------------------------------------------------------------\n" RESET);
    #endif
    
    sscanf(compile_struct->buffer, "%s", compile_struct->cmdStr); 
    // ONDEBUGASM(fprintf(stdout, "\ncompile_struct.cmdStr_after_label = %s\n", compile_struct->cmdStr));
    
    for (*i = 0;CountHash(compile_struct->cmdStr) != arr_command[*i].command_hash ; (*i)++) 
    {
        // ONDEBUGASM(printf(BOLD_GREEN "i = %d\n" RESET, *i));
        // PRINT_DEBUG(BOLD_GREEN, "arr_command[%d] = %s\n", *i, arr_command[*i].command_name);

        if (*i == num_command - 2)
        {
            printf(BOLD_RED "\nUnknown command: %s!!!\n\n" RESET, compile_struct->cmdStr);
            return ERR;
        }
    }

    compile_struct->buffer = skip_space(compile_struct->buffer);
    compile_struct->count_element++;

    return OK;    
}

int Assembler_Jump           (Assembler_t* assembler, Compile_t* compile_struct)

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

int Assembler_Register_Arg   (Compile_t* compile_struct)
{
    compile_struct->buffer = skip_space(compile_struct->buffer);

    char name[10] = ""; 
    if (sscanf(compile_struct->buffer, "%s", name) != 1) return ERR;

    if (name[0] != 'R' || name[2] != 'X') 
    {
        printf(RED "Error format register!\n" RESET);
        return ERR;
    }

    ONDEBUGASM(fprintf(fileerr, "register name[1] - A = %d\n", name[1] - 'A'));

    PUSH(compile_struct->stack, name[1] - 'A' + 1);

    compile_struct->buffer += 4;
    compile_struct->count_element++;

    return OK;
}

int Assembler_RAM            (Compile_t* compile_struct)
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

int Assembler_Push           (Compile_t* compile_struct)
{
    int elem = 0;
    
    // PRINT_DEBUG(BLUE, "buffer_before_skip = %.10s\n", compile_struct->buffer);
    
    compile_struct->buffer = skip_space(compile_struct->buffer);
            
    ONDEBUGASM(printf("string = [%.10s] \n", compile_struct->buffer));

    if (sscanf(compile_struct->buffer, TYPEELEM, &elem) != 1) 
        {
        printf(RED "\nError read arg in push\n" RESET);
        return ERR;
    }
    
    ONDEBUGASM(printf(BOLD_BLUE "elem in push = " TYPEELEM "\n", elem));
    PUSH(compile_struct->stack, elem)

    compile_struct->count_element++;

    return OK;
}

int Assembler_get_arg       (Assembler_t* assembler, Compile_t* compile_struct, int command_index)
{
    int err = 0;

    if (command_index == PUSH_G) { 
            Assembler_Push(compile_struct);
        }
        
        if (command_index >= JB_G && command_index <= CALL_G) {
            err = Assembler_Jump(assembler, compile_struct);

            if (err)
            {
                printf(RED "Error Jump\n" RESET);
                return ERR;
            }
        }

        else if (command_index == PUSHR_G || command_index == POPR_G) { 
            Assembler_Register_Arg(compile_struct);
        }

        else if (command_index == PUSHM_G || command_index == POPM_G) { 
            err = Assembler_RAM(compile_struct);

            if (err)
            {
                printf(RED "Error format pushm\n" RESET);
                return ERR;
            }
        }

    return OK;
}

void WriteBiteCodeFile(FILE* bitecode, int* arr, size_t count_element) {
    // for (int i = 0; i < count_element; i++) {
        // fprintf(bitecode, "%d ", arr[i]);
    // }
    fwrite(arr, count_element, sizeof(int), bitecode);
}

size_t CountHash(const char* string)
{
    size_t hash = 0;

    while (*string != '\0')
    {
        hash = hash * 91 + *string;
        string++;
    }

    return hash;
}