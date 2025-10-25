#include "asm.h"

//2 542 3 2 7 1 4 6 3

//2 80 2 40 54

int num_command = 30;

void Compile(const char* commandfile, Assembler_t* assembler, Command_t* arr_command) 
{
    Compile_t compile_struct = {};
    CompileCtor(commandfile, &compile_struct);

    int err = 0;
    int index_string = 0;
 
    while (1) {
        PRINT_DEBUG(BOLD_CYAN, "INDEX_STRING = %d\n\n", index_string);

        compile_struct.arr_string[index_string].str = skip_space_end(compile_struct.arr_string[index_string].str, compile_struct.arr_string[index_string].str_end);
        char* string_assembler = skip_space(compile_struct.arr_string[index_string].str);

        if (string_assembler[0] == '\0' || string_assembler[0] == ';')
        {
            index_string++;
            continue;
        }

        PRINT_DEBUG(BOLD_CYAN, "string[%d] = [%s]\n", index_string, string_assembler);

        sscanf(string_assembler, "%s", compile_struct.cmdStr);      
        ONDEBUGASM(fprintf(stdout, "%s:%d: compile_struct->cmdStr = %s\n", __FILE__, __LINE__, compile_struct.cmdStr));
        
        if (compile_struct.cmdStr[0] == ':') 
        {
            err = Assembler_Write_label(assembler, &compile_struct, string_assembler);
            index_string++;
            BREAK
            continue;
        }

        int command_index = 0;
        err = Assembler_Search_Command(&compile_struct, &command_index, arr_command, string_assembler);
        
        BREAK

        fprintf(file_listing, "%3d:       %-8d%-8s\n" , compile_struct.count_element, arr_command[command_index].command_code, string_assembler);
        string_assembler += arr_command[command_index].command_size;


        PRINT_DEBUG(BOLD_BLUE, "\ncommand_name = [%s]\n", arr_command[command_index].command_name);
        PRINT_DEBUG(MAGENTA,"\ncommand_hash = [%zu]\n", arr_command[command_index].command_hash);
        PRINT_DEBUG(GREEN,  "command_code = [%d]\n\n", arr_command[command_index].command_code);

        PUSH(compile_struct.stack, arr_command[command_index].command_code);
        
        err = Assembler_get_arg(assembler, &compile_struct, command_index, string_assembler);

        
        // BREAK
        
        index_string++;
        
        PRINT_DEBUG(BOLD_MAGENTA, " after get_arg\n");

        PRINT_DEBUG(BOLD_MAGENTA, "count_string = [%d]\n", compile_struct.count_string);

        if (index_string == compile_struct.count_string)
            break;
        
        // int c = getchar();
    }

    // открывать файл с байт-кодом и печатать его туда
    FILE* bitecode = fopen("bitecode.bin", "wb");
    fprintf(fileerr, "count_elem = %d\n", compile_struct.count_element);

    assembler->label_count = assembler->label_index;
    assembler->label_index = 0;

    WriteBiteCodeFile(bitecode, compile_struct.stack.data, compile_struct.count_element);
    
    // PRINT_DEBUG(BOLD_MAGENTA, "arr_string[0] = [%c]")
    free(compile_struct.arr_string[0].str - 1); 
    CompileDtor(&compile_struct);
    if (bitecode) fclose(bitecode);
    // return stack.data;
}

void CompileCtor(const char* commandfile, Compile_t* compile_struct)
{
    Buffer struct_buffer = CreateBuffer(commandfile);
    compile_struct->count_string = (int) CountStr(struct_buffer.buff + 1);
    
    String_t* arr_string= (String_t* ) calloc(compile_struct->count_string + 1, sizeof(String_t));

    // PRINT_DEBUG(BOLD_YELLOW, "с = %c\n", struct_buffer.buff[1]);

    CreateArrPoint(arr_string, struct_buffer.buff + 1);


    INITSTACK(compile_struct->stack, 7);

    compile_struct->arr_string = arr_string;
    compile_struct->count_element = 0;
    compile_struct->cmdStr = (char* ) calloc(30, sizeof(char));

    // free(struct_buffer.buff);
}

void CompileDtor(Compile_t* compile_struct)
{
    free(compile_struct->cmdStr);
    DTOR(compile_struct->stack);
}

int Assembler_Write_label    (Assembler_t* assembler,  Compile_t* compile_struct, char* string_assembler)
{
    #ifdef DEBUG_ASSEMBLER
            printf("label = %s\n", compile_struct->cmdStr);
            // printf("buffer[0] = %c, buffer[1] = %c\n", compile_struct->buffer[0], compile_struct->buffer[1]);
    #endif

    #ifdef DEBUG_ASSEMBLER
        // printf("%d\n", sscanf(buffer, "%d", &assembler->label.->label_name));
        // label[label_index] = count_element;
    #endif

    char label_name[30] = "";
    if (sscanf(string_assembler, "%s", label_name) != 1)
    {
        printf(BOLD_RED "Error reading label name\n");
        return ERR;
    }
    
    assembler->label[assembler->label_index].label_hash = CountHash(label_name);
    assembler->label[assembler->label_index].label_value = compile_struct->count_element; 

    #ifdef DEBUG_ASSEMBLER
        printf(BLUE "-----------------------------------------------------------------------\nSTART label\n\n");
        printf("label[%d] = %zu %d\n",assembler->label_index, assembler->label[assembler->label_index].label_hash, assembler->label[assembler->label_index].label_value);
        printf("\nEND label\n-----------------------------------------------------------------------\n\n" RESET);
    #endif

    assembler->label_index++;
    
    // ONDEBUGASM(printf("str_after_label = [%.20s]\n", compile_struct->buffer));

    return OK;
}

int Assembler_Search_Command (Compile_t* compile_struct, int* command_index, Command_t* arr_command, char* string_assembler)

{    
    // #ifdef DEBUG_ASSEMBLER
    //     printf(BOLD_GREEN "----------------------------------------------------------------------------------------\nIn Search_Commnad\n");
    //     printf("i = %d\n", *i);
    //     printf("----------------------------------------------------------------------------------------\n" RESET);
    // #endif
    
    sscanf(string_assembler, "%s", compile_struct->cmdStr); 
    ONDEBUGASM(fprintf(stdout, "\ncompile_struct.cmdStr = %s\n", compile_struct->cmdStr));
    
    for (*command_index = 0; CountHash(compile_struct->cmdStr) != arr_command[*command_index].command_hash ; (*command_index)++) 
    {
        // ONDEBUGASM(printf(BOLD_GREEN "commad_index = %d\n" RESET, *command_index));
        // PRINT_DEBUG(BOLD_GREEN, "arr_command[%d] = %s\n", *command_index, arr_command[*command_index].command_name);

        if (*command_index == num_command - 2)
        {
            printf(BOLD_RED "\nUnknown command: %s!!!\n\n" RESET, compile_struct->cmdStr);
            return ERR;
        }
    }

    compile_struct->count_element++;

    return OK;    
}

int Assembler_Jump           (Assembler_t* assembler, Compile_t* compile_struct, char* string_assembler)

{
    string_assembler = skip_space(string_assembler);

    char jmp_arg[40] = ""; 
    sscanf(string_assembler, "%s", jmp_arg);

    char label_name[40] = "";

    if (jmp_arg[0] == ':')
        sscanf(string_assembler + 1, "%s", label_name);
    else
        return ERR;

    ONDEBUGASM(printf("%s\n", label_name)); 
    int i = 0;
    ONDEBUGASM(printf(RED "label_index = %d\n" RESET, assembler->label_index));

    if (assembler->label_count <= assembler->label_index)
        assembler->label_count = assembler->label_index;

    for (; i < assembler->label_count; i++)
    {
        if (assembler->label[i].label_hash == CountHash(label_name))
            break;
    }

    #ifdef DEBUG_ASSEMBLER
        printf(MAGENTA"------------------------------------------------------------------\nJUMP\n\n");
        printf("index_in_label = %d\n", i);
        printf("elem = %d\n", assembler->label[i].label_value);
        printf("label_name = %d\n", assembler->label[i].label_hash);
        printf("\nEND_OF_JUMP\n------------------------------------------------------------------\n" RESET);
    #endif

    PUSH(compile_struct->stack, assembler->label[i].label_value);
    compile_struct->count_element++;

    return OK;
}

int Assembler_Register_Arg   (Compile_t* compile_struct, char* string_assembler)
{
    string_assembler = skip_space(string_assembler);

    char name[10] = ""; 
    if (sscanf(string_assembler, "%s", name) != 1) return ERR;

    if (name[0] != 'R' || name[2] != 'X') 
    {
        printf(RED "Error format register!\n" RESET);
        return ERR;
    }

    ONDEBUGASM(fprintf(fileerr, "register name[1] - A = %d\n", name[1] - 'A'));

    PUSH(compile_struct->stack, name[1] - 'A' + 1);

    // string_assembler += 4;
    compile_struct->count_element++;

    return OK;
}

int Assembler_RAM            (Compile_t* compile_struct, char* string_assembler)
{
    string_assembler = skip_space(string_assembler);

    char name[10] = ""; 
    sscanf(string_assembler, "%s", name);
    // ONDEBUGASM(printf(BOLD_RED "name in popm = %.20s\n" RESET, compile_struct->buffer));

    if (name[0] !=  '[')
    {
        return ERR;
    }

    fprintf(fileerr, "register name[1] - A = %d\n", name[2] - 'A');
    PUSH(compile_struct->stack, name[2] - 'A' + 1);
    // compile_struct->buffer += 6;

    compile_struct->count_element++;

    return OK;
}

int Assembler_Push           (Compile_t* compile_struct, char* string_assembler)
{
    int elem = 0;
    
    // PRINT_DEBUG(BLUE, "buffer_before_skip = %.10s\n", compile_struct->buffer);
    
    string_assembler = skip_space(string_assembler);
            
    PRINT_DEBUG(BOLD_CYAN, "string_assembler = [%s]\n", string_assembler);

    if (sscanf(string_assembler, TYPEELEM, &elem) != 1) 
        {
        printf(RED "\nError read arg in push\n" RESET);
        return ERR;
    }
    
    ONDEBUGASM(printf(BOLD_BLUE "elem in push = " TYPEELEM "\n", elem));
    PUSH(compile_struct->stack, elem)

    compile_struct->count_element++;

    return OK;
}

int Assembler_get_arg       (Assembler_t* assembler, Compile_t* compile_struct, int command_index, char* string_assembler)
{
    int err = 0;

    // PRINT_DEBUG(BOLD_MAGENTA, " in get_arg\n");
    if (command_index == PUSH_G) { 
            Assembler_Push(compile_struct, string_assembler);
        }
        
        if (command_index >= JB_G && command_index <= CALL_G) {
            err = Assembler_Jump(assembler, compile_struct, string_assembler);

            if (err)
            {
                printf(RED "Error Jump\n" RESET);
                return ERR;
            }
        }

        else if (command_index == PUSHR_G || command_index == POPR_G) { 
            Assembler_Register_Arg(compile_struct, string_assembler);
        }

        else if (command_index == PUSHM_G || command_index == POPM_G) { 
            err = Assembler_RAM(compile_struct, string_assembler);

            if (err)
            {
                printf(RED "Error format pushm\n" RESET);
                return ERR;
            }
        }

    // PRINT_DEBUG(BOLD_MAGENTA, " in get_arg\n");

    return OK;
}

void WriteBiteCodeFile(FILE* bitecode, int* arr, size_t count_element) {
    // for (int i = 0; i < count_element; i++) {
        // fprintf(bitecode, "%d ", arr[i]);
    // }
    fwrite(arr, count_element, sizeof(int), bitecode);
}

size_t CountHash(const char* str)
{
    size_t hash = 0;

    while (*str != '\0')
    {
        hash = hash * 91 + *str;
        str++;
    }

    return hash;
}