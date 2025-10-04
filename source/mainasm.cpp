#include "mainasm.h"

FILE* fileerr = fopen("Logfile.log", "w");

int main() {
    ConvertToBite("commandfile.txt");

    // for (int i = 0; arr[i] != 0; i++) {
    //     printf("%d ", arr[i]);
    // }

    fclose(fileerr);
}