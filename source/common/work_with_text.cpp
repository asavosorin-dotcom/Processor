#include "work_with_text.h"

Buffer CreateBuffer(const char* filename) {
    
    // Buffer* point_struct = (Buffer* ) calloc(1, sizeof(Buffer));
    Buffer point_struct = {0};
    // assert(struct_buf);

    FILE* file = fopen(filename, "r");

    assert(file);

    size_t numOfElem    = SizeOfFile(filename) / sizeof(char);
    char* buffer        = (char* ) calloc(numOfElem + 20, sizeof(char));
    size_t numOfElemNew = fread(buffer + 1, sizeof(char), numOfElem + 2, file);

    // point_struct->buff = buffer;
    // point_struct->buff_size = numOfElemNew;

    point_struct.buff = buffer;
    point_struct.buff_size = numOfElemNew;  

    fclose(file);

    return point_struct;
}

BufferBin CreateBufferBinary(const char* filename) {
    
    // Buffer* point_struct = (Buffer* ) calloc(1, sizeof(Buffer));
    BufferBin point_struct = {0};
    // assert(struct_buf);

    FILE* file = fopen(filename, "rb");

    assert(file);

    size_t numOfElem = SizeOfFile(filename) / sizeof(int);
    int*   buffer    = (int* ) calloc(numOfElem + 1, sizeof(int));

    fread(buffer, sizeof(int), numOfElem + 1, file);

    // point_struct->buff = buffer;
    // point_struct->buff_size = numOfElemNew;

    point_struct.buff = buffer;
    point_struct.buff_size = numOfElem;  

    fclose(file);

    return point_struct;
}

size_t SizeOfFile(const char* filename) {
    
    assert(filename);

    struct stat my_stat = {};
    int description = open(filename,  O_RDONLY);
    
    assert(description != -1);

    fstat(description, &my_stat);

    // printf("Size = %ld\n", my_stat.st_size);

    return (size_t) my_stat.st_size;
}

size_t CountStr(const char* buffer) {
    
    size_t count = 0;
    
    while (*buffer != '\0') {
        
        if (*buffer == '\n') {
            count++;
            buffer++;

            while (*buffer == '\n') {
                buffer++;
            }
        } else {
            buffer++;
        }
           
    }

    // printf("Count = %d\n\n", count + 1);

    return ++count;
}

void OutPutBuf(char* buffer, FILE* fileout, size_t numOfElemNew) {
    for (size_t i = 0; i < numOfElemNew; i++) {
        fputc(buffer[i]? buffer[i] : '\n', fileout);

        if (buffer[i] == '\n')
            fputs("\\n \n", fileout);

        if (buffer[i] == '\0')
            fprintf(fileout, "0\n");
    }
        

}

size_t Maxlen(char* buffer) {
    
    int maxlen = 0;
    int count = 0;

    while (*buffer != '\0') {
        if (*buffer == '\n') {
            
            if (count > maxlen)
                maxlen = count;

            count = 0;
        }

        buffer++;
        count++;
    }

    printf("MaxLen = %d\n", maxlen);

    return (size_t) maxlen;
}

char* skip_space(char* buffer)
{
    while (isspace(*buffer)) {
            buffer++;
        }

    return buffer;
}