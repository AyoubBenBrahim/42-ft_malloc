#include <stdlib.h>
#include <unistd.h>
#include "../inc/malloc.h"

int main()
{
    void *q = malloc(102);
    memccpy(q, "Hello World", 0, 12);
    malloc(1024);
    // void *a = malloc(1024);
    // void *b = malloc(1024);
    // void *c = malloc(1024);
    // void *d = malloc(1024);
    // free(c);
    // free(b);
    malloc(1024 * 32);
    malloc(1024 * 1024);
    malloc(1024 * 1024 * 16);
    malloc(1024 * 1024 * 128);
    show_alloc_mem();
    // show_alloc_mem_ex(q, 1);
    return (0); 
}