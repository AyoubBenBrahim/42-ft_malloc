#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char etext, edata, end; // Symbols defined by the linker

int main() {
    void* current_brk = sbrk(0);
    void* data_end = &edata; // Address of the end of the data section

    printf("Current program break: %p\n", current_brk);
    printf("End of data section: %p\n", data_end);
    printf("End of program (end symbol): %p\n", &end);

    return 0;
}