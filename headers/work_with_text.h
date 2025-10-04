#ifndef _WORK_
#define _WORK_

#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/stat.h>

#include <string.h>
#include <stdlib.h>
//' ', ' ', 5

//sscanf(buff + i, "%d")
//%n

typedef struct {
    char* buff;
    size_t buff_size;
} Buffer;

size_t SizeOfFile(const char* filename);
size_t Maxlen(char* buffer);
size_t CountStr(const char* buffer);
void OutPutBuf(char* buffer, FILE* fileout, size_t numOfElemNew);

Buffer CreateBuffer(const char* filename);

#endif