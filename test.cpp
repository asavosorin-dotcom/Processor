#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int CountHash(const char* string);

int main() 
{
    const char* string = "JA\0";
    printf("hash = %d\n", CountHash(string));    
}

int CountHash(const char* string)
{
    int hash = 0;

    while (*string != '\0')
    {
        printf("meow\n");
        printf("[%c] = [%d]\n", *string, *string);
        hash = hash * 91 + *string;
        string++;
    }

    return hash;
}