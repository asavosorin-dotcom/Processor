#include "bite.h"

StackElement_t* TextConvertToBite(const char* filename) {

    Buffer struct_buffer = CreateBuffer(filename);

    char* buffer = struct_buffer.buff;
    assert(buffer);

    buffer++;
    // printf("%c\n", *buffer);
    Stack_t arr = {};
    INITSTACK(arr, 7);

    StackElement_t elem = 1;

    while(elem != 0) {
        while (isspace(*buffer))
            buffer++;
        
        sscanf(buffer, TYPEELEM, &elem);
        // printf("elem = "TYPEELEM"\n", elem);
        PUSH(arr, elem);
        // PRINTELEM(elem);

        if (elem == 0)
            break;
        
        buffer = strchr(buffer, ' ');

        // printf("buffer = %c", *buffer);
    }

    PRINTSTACK(arr);

    free(struct_buffer.buff);
    return arr.data;
}