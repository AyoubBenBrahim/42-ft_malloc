
# include "../inc/malloc.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

    char *ptr1, *ptr2, *ptr3, *ptr4, *ptr5, *ptr6, *ptr7, *ptr8, *ptr9, *ptr10, *ptr11;


    ptr1 = my_malloc(10);
    ptr2 = my_malloc(100);
    ptr3 = my_malloc(1000);
    ptr4 = my_malloc(10000);
    ptr5 = my_malloc(100000);
    ptr6 = my_malloc(1000000);
    ptr7 = my_malloc(10000000);
    ptr8 = my_malloc(100000000);
    ptr9 = my_malloc(1000000000);
    ptr10 = my_malloc(10000000000);
    ptr11 = my_malloc(100000000000);

    strcpy(ptr1, "Ten");
    strcpy(ptr2, "Hundred");
    strcpy(ptr3, "Thousand");
    strcpy(ptr4, "Ten Thousand");
    strcpy(ptr5, "Hundred Thousand");
    strcpy(ptr6, "Million");
    strcpy(ptr7, "Ten Million");
    strcpy(ptr8, "Hundred Million");
    strcpy(ptr9, "Billion");
    strcpy(ptr10, "Ten Billion");
    strcpy(ptr11, "Hundred Billion");

    printf("%s\n", ptr6);
    printf("%s\n", ptr7);
    printf("%s\n", ptr8);
    printf("%s\n", ptr9);
    printf("%s\n", ptr10);
    printf("%s\n", ptr11);

    my_free(ptr1);
    my_free(ptr2);
    my_free(ptr3);
    my_free(ptr4);

    ptr1 = my_malloc(1000000000000);
    ptr2 = my_malloc(10000000000000);
    
    ptr3 = my_malloc(100000000000000);
    ptr4 = my_malloc(1000000000000000); // mmap returns  0xffffffffffffffff = -1 = MAP_FAILED
    printf("ptr4 %%p %p\n", ptr4);
    
    /*
    ** the operating system typically searches for a contiguous block of virtual memory 
    ** that meets the requested size and alignment requirements. The virtual memory 
    ** represents the address space available to a process.

    ** If the operating system cannot find a contiguous block of memory that satisfies the mmap request,
    ** it may return MAP_FAILED (-1) to indicate failure.
    */

    strcpy(ptr1, "Trillion");
    strcpy(ptr2, "Ten Trillion");
    strcpy(ptr3, "Hundred Trillion");

    printf("%s\n", ptr1);
    printf("%s\n", ptr2);
    printf("%s\n", ptr3);

    // print_bins();
    // print_arenas();
    // show_alloc_mem();
}