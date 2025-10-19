#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* skip_space(char* buffer);

int main() {
    char* buffer = (char* ) calloc(30, sizeof(char));
    strcpy(buffer, "             125");

    buffer = skip_space(buffer);
    printf("%s\n", buffer);
}

char* skip_space(char* buffer)
{
    while (isspace(*buffer)) {
            buffer++;
        }

    return buffer;
}