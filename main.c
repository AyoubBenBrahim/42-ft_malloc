# include "inc/malloc.h"
# include <stdio.h>

int main() {
   
    char *ptr1;
    char *ptr2;
    char *ptr3;

    ptr1 = (char *)my_malloc(10);
    strcpy(ptr1, "Hello");
    ptr2 = (char *)my_malloc(100);
    strcpy(ptr2, "World");
    ptr3 = (char *)my_malloc(1000);
    strcpy(ptr3, "Hello World");

    printf("ptr1: %s\n", ptr1);
    printf("ptr2: %s\n", ptr2);
    printf("ptr3: %s\n", ptr3);

    // show_alloc_mem();
    // print_bins();
    // print_arenas();

    // my_free(ptr1);
    // my_free(ptr2);
    // my_free(ptr3);

    // print_bins();
}