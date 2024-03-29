#include <strings.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "../inc/malloc.h"

#define M (1024 * 1024)

void print(char *s)
{
    write(1, s, strlen(s));
}

int main()
{ 
    char *addr1; char *addr3;

    addr1 = (char*)malloc(16*M);
    show_alloc_mem();
    strcpy(addr1, "Hello world!\n");
    print(addr1);
    addr3 = (char*)realloc(addr1, 128*M);
    show_alloc_mem();
    addr3[127*M] = 42;
    print(addr3);
    return (0);
}
