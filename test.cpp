#include "TX/TXLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int CountHash(const char* string);

int main() 
{
    printf("%d\n", isspace('\r'));
    return 0;  
}

int CountHash(const char* str)
{
    int hash = 0;

    while (*str != '\0')
    {
        printf("meow\n");
        printf("[%c] = [%d]\n", *str, *str);
        hash = hash * 91 + *str;
        str++;
    }

    return hash;
}