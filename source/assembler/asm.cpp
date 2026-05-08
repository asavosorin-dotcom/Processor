#include "../../headers/asm.h"

void Compile(const char* commandfile, Assembler_t* assembler, Command_t* arr_command) 
{
    Compile_t compile_struct = {};
    CompileCtor(commandfile, &compile_struct);

    int err = 0;
    int index_string = 0;
 
    while (1) {
        // PRINT_DEBUG(BOLD_CYAN, "INDEX_STRING = %d\n\n", index_string);

        compile_struct.arr_string[index_string].str = skip_space_end(compile_struct.arr_string[index_string].str, compile_struct.arr_string[index_string].str_end);
        char* string_assembler = skip_space(compile_struct.arr_string[index_string].str);

        if (string_assembler[0] == '\0' || string_assembler[0] == ';')
        {
            index_string++;
            continue;
        }

        // операнды в файл-листинг

        // PRINT_DEBUG(BOLD_CYAN, "string[%d] = [%s]\n", index_string, string_assembler);

        sscanf(string_assembler, "%s", compile_struct.cmdStr);      
        // ONDEBUGASM(fprintf(stdout, "%s:%d: compile_struct->cmdStr = %s\n", __FILE__, __LINE__, compile_struct.cmdStr));
        
        if (compile_struct.cmdStr[0] == ':') 
        {
            err = Assembler_Write_label(assembler, &compile_struct, string_assembler);
            index_string++;
            BREAK
            continue;
        }

        Command_t command = {};
        Command_t* command_point = &command;

        err = Assembler_Search_Command(&compile_struct, &command_point, arr_command, string_assembler);
        
        BREAK
        
        // if (arr_command[command_index].command_code < )

        string_assembler += command_point->command_size;
        
        
        // PRINT_DEBUG(BOLD_BLUE, "\ncommand_name = [%s]\n" , command_point->command_name);
        // PRINT_DEBUG(MAGENTA  , "\ncommand_hash = [%zu]\n", command_point->command_hash);
        // PRINT_DEBUG(GREEN    , "command_code = [%d]\n\n" , command_point->command_code);
        
        PUSH(compile_struct.stack, command_point->command_code);
        
        int arg = 0;
        // printf("arg = [%p]", arg);
        err = Assembler_get_arg(assembler, &compile_struct, *command_point, string_assembler, &arg);

        if (err == ARG)
            fprintf(file_listing, "%3d:       %-2d %-4d" , compile_struct.count_element - 2, command_point->command_code, arg);
        else
            fprintf(file_listing, "%3d:       %-7d" , compile_struct.count_element - 1, command_point->command_code);

        fprintf(file_listing, "%-8c", ' ');
        fprintf(file_listing, "%-8s\n", skip_space(compile_struct.arr_string[index_string].str));

        // BREAK
        
        index_string++;
        
        // PRINT_DEBUG(BOLD_MAGENTA, " after get_arg\n");

        PRINT_DEBUG(BOLD_MAGENTA, "count_string = [%d]\n", compile_struct.count_string);

        if (index_string == compile_struct.count_string)
            break;
        
        // int c = getchar();
    }

    // открывать файл с байт-кодом и печатать его туда
    FILE* bytecode = fopen("bytecode.bin", "wb");
    fprintf(fileerr, "count_elem = %d\n", compile_struct.count_element);

    assembler->label_count = assembler->label_index;
    assembler->label_index = 0;

    WriteByteCodeFile(bytecode, compile_struct.stack.data, compile_struct.count_element);
    
    // PRINT_DEBUG(BOLD_MAGENTA, "arr_string[0] = [%c]")
    free(compile_struct.arr_string[0].str - 1); 
    CompileDtor(&compile_struct);
    if (bytecode) fclose(bytecode);
    // return stack.data;
}

void CompileCtor(const char* commandfile, Compile_t* compile_struct)
{
    Buffer struct_buffer = CreateBuffer(commandfile);
    compile_struct->count_string = (int) CountStr(struct_buffer.buff + 1);
    
    String_t* arr_string = (String_t* ) calloc(compile_struct->count_string + 1, sizeof(String_t));

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
    free(compile_struct->arr_string);
}

int Assembler_Write_label    (Assembler_t* assembler,  Compile_t* compile_struct, char* string_assembler)
{
    #ifdef DEBUG_LABEL
            printf("label = %s\n", compile_struct->cmdStr);
            // printf("buffer[0] = %c, buffer[1] = %c\n", compile_struct->buffer[0], compile_struct->buffer[1]);
    #endif

    #ifdef DEBUG_LABEL
        // printf("%d\n", sscanf(buffer, "%d", &assembler->label.->label_name));
        // label[label_index] = count_element;
    #endif

    char label_name[30] = "";
    if (sscanf(string_assembler + 1, "%s", label_name) != 1)
    {
        printf(BOLD_RED "Error reading label name\n");
        return ERR;
    }
    
    assembler->label[assembler->label_index].label_hash = CountHash(label_name);
    assembler->label[assembler->label_index].label_value = compile_struct->count_element; 
    
    #ifdef DEBUG_LABEL
        printf(BLUE "-----------------------------------------------------------------------\nSTART label\n\n");
        printf("label name = [%s]\n", label_name);
        printf("label[%d] = %zu %d\n",assembler->label_index, assembler->label[assembler->label_index].label_hash, assembler->label[assembler->label_index].label_value);
        printf("\nEND label\n-----------------------------------------------------------------------\n\n" RESET);
    #endif

    assembler->label_index++;
    
    // ONDEBUGASM(printf("str_after_label = [%.20s]\n", compile_struct->buffer));

    return OK;
}

// двоичный поиск

int Assembler_Search_Command (Compile_t* compile_struct, Command_t** command, Command_t* arr_command, char* string_assembler)
{    
    assert(command);
    
    // #ifdef DEBUG_ASSEMBLER
    //     printf(BOLD_GREEN "----------------------------------------------------------------------------------------\nIn Search_Commnad\n");
    //     printf("i = %d\n", *i);
    //     printf("----------------------------------------------------------------------------------------\n" RESET);
    // #endif
    
    // PRINT_DEBUG(BOLD_RED, "num_command = %d\n", num_command);

    sscanf(string_assembler, "%s", compile_struct->cmdStr); 
    // PRINT_DEBUG(BOLD_MAGENTA, "\ncompile_struct.cmdStr = %s\n", compile_struct->cmdStr);
    
    qsort(arr_command, ARR_COMMAND_SIZE, sizeof(arr_command[0]), compar_command);

    Command_t command_key = {};
    command_key.command_hash = CountHash(compile_struct->cmdStr);

    *command = (Command_t* ) bsearch(&command_key, arr_command, ARR_COMMAND_SIZE, sizeof(arr_command[0]), compar_command);

    // printf("command_code = %d\n", *command->command_code);

    if (command == NULL)
    {
        printf(BOLD_RED "\nUnknown command: %s!!!\n\n" RESET, compile_struct->cmdStr);
        return ERR;
    }

    compile_struct->count_element++;

    return OK;    
}

int Assembler_Jump           (Assembler_t* assembler, Compile_t* compile_struct, char* string_assembler, int* arg)

{
    string_assembler = skip_space(string_assembler);

    char jmp_arg[40] = ""; 
    sscanf(string_assembler, "%s", jmp_arg);

    char label_name[40] = "";

    if (jmp_arg[0] == ':')
        sscanf(string_assembler + 1, "%s", label_name);
    else
        return ERR;

    printf("%s\n", label_name); 
    // printf(RED "label_index = %d\n" RESET, assembler->label_index);

    size_t label_hash = CountHash(label_name);
    PRINT_DEBUG(BOLD_MAGENTA, "hash = %zu\n", label_hash);
    qsort(assembler->label, assembler->label_size, sizeof(assembler->label[0]), compar_label);
    PRINT_DEBUG(BOLD_GREEN, "compar label[0], label[1] = %d\n\n", compar_label(&assembler->label[8], &assembler->label[9]));

    // PRINT_DEBUG(BOLD_CYAN, "label_value = %d\n", assembler->label[0].label_value);
    Label_t label_key = {};
    label_key.label_hash = label_hash;
    Label_t* label = (Label_t* ) bsearch(&label_key, assembler->label, assembler->label_size, sizeof(assembler->label[0]), compar_label);

    if (label == NULL)
    {
        compile_struct->count_element++;
        return OK;
    }

    #ifdef DEBUG_LABEL
        printf(MAGENTA"------------------------------------------------------------------\nJUMP\n\n");
        printf(":%s:%d ", __FILE__, __LINE__);
        printf("index_in_label = %d\n", i);
        printf("elem = %d\n", assembler->label[i].label_value);
        printf("label_name = %d\n", assembler->label[i].label_hash);
        printf("\nEND_OF_JUMP\n------------------------------------------------------------------\n" RESET);
    #endif

    *arg = label->label_value;
    PUSH(compile_struct->stack, label->label_value);

    compile_struct->count_element++;

    return OK;
}

int Assembler_Register_Arg   (Compile_t* compile_struct, char* string_assembler, int* arg)
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

    *arg = name[1] - 'A' + 1;
    PUSH(compile_struct->stack, name[1] - 'A' + 1);

    // string_assembler += 4;
    compile_struct->count_element++;

    return OK;
}

int Assembler_RAM            (Compile_t* compile_struct, char* string_assembler, int* arg)
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
    *arg = name[2] - 'A' + 1;
    PUSH(compile_struct->stack, name[2] - 'A' + 1);
    // compile_struct->buffer += 6;

    compile_struct->count_element++;

    return OK;
}

int Assembler_Push           (Compile_t* compile_struct, char* string_assembler, int* arg)
{
    int elem = 0;
    
    // PRINT_DEBUG(BLUE, "buffer_before_skip = %.10s\n", compile_struct->buffer);
    
    string_assembler = skip_space(string_assembler);
            
    // PRINT_DEBUG(BOLD_CYAN, "string_assembler = [%s]\n", string_assembler);

    if (sscanf(string_assembler, TYPEELEM, &elem) != 1) 
    {
        printf(RED "\nError read arg in push\n" RESET);
        return ERR;
    }
    
    ONDEBUGASM(printf(BOLD_BLUE "elem in push = " TYPEELEM "\n", elem));

    *arg = elem;
    PUSH(compile_struct->stack, elem)

    compile_struct->count_element++;

    return OK;
}

int Assembler_get_arg        (Assembler_t* assembler, Compile_t* compile_struct, Command_t command, char* string_assembler, int* arg)
{
    int err = 0;

    // PRINT_DEBUG(BOLD_MAGENTA, " in get_arg\n");
    if (command.command_code == PUSH_G) { 
            Assembler_Push(compile_struct, string_assembler, arg);
            return ARG;
    }
        
    if (command.command_code >= JB_G && command.command_code <= CALL_G) {
        err = Assembler_Jump(assembler, compile_struct, string_assembler, arg);
        if (err)
        {
            printf(RED "Error Jump\n" RESET);
            return ERR;
        }

        return ARG;
    }

    else if (command.command_code == PUSHR_G || command.command_code == POPR_G) { 
        Assembler_Register_Arg(compile_struct, string_assembler, arg);
        return ARG;
    }

    else if (command.command_code == PUSHM_G || command.command_code == POPM_G) { 
        err = Assembler_RAM(compile_struct, string_assembler, arg);

        if (err)
        {
            printf(RED "Error format pushm\n" RESET);
            return ERR;
        }

        return ARG;
    }

    // PRINT_DEBUG(BOLD_MAGENTA, " in get_arg\n");

    return OK;
}

void WriteByteCodeFile(FILE* bytecode, StackElement_t* arr, size_t count_element) {
    // for (int i = 0; i < count_element; i++) {
        // fprintf(bytecode, "%d ", arr[i]);
    // }
    fwrite(arr, count_element, sizeof(int), bytecode);
}

size_t CountHash(const char* str)
{
    size_t hash = 0;

    while (*str != '\0')
    {
        hash = hash * 31 + *str;
        str++;
    }

    return hash;
}

int compar_label (const void* label_1, const void* label_2)
{
    if (((const Label_t* )label_1)->label_hash > ((const Label_t* )label_2)->label_hash)
        return ABOVE;
    else if (((const Label_t* )label_1)->label_hash == ((const Label_t* )label_2)->label_hash)
        return EQUAL;
    else 
        return BELOW;
    
}

int compar_command (const void* command_1, const void* command_2)
{
    if (((const Command_t* )command_1)->command_hash > ((const Command_t* )command_2)->command_hash)
        return ABOVE;

    else if (((const Command_t* )command_1)->command_hash == ((const Command_t* )command_2)->command_hash)
        return EQUAL;

    else 
        return BELOW;
}
