#include "../inc/malloc.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void test_large_bin()
{
    char* ptr = (char*)ft_malloc(200);
    char* ptr2 = (char*)ft_malloc(200);
    char* ptr3 = (char*)ft_malloc(200);
    char* ptr4 = (char*)ft_malloc(700);
    char* ptr5 = (char*)ft_malloc(600);
    
    print_bins();
    
    ft_printf("\n\n");

    ft_printf("ret_ptr1 = %p\n", ptr);
    ft_printf("ret_ptr2 = %p\n", ptr2);
    ft_printf("ret_ptr3 = %p\n", ptr3);
    ft_printf("--------------------\n");

    ft_free(ptr);
    ft_printf("--------------------\n");
    ft_free(ptr2);
    ft_printf("--------------------\n");
    ft_free(ptr3);
    ft_printf("--------------------\n");
    ft_free(ptr4);

    ft_printf("\n\n                 #### after free #####\n\n");
    print_bins();
}

void test_tiny_bin()
{
    char* ptr600 = (char*)ft_malloc(600);
    char* ptr1 = (char*)ft_malloc(10);
    // char* ptr3 = (char*)ft_malloc(60);
    // char* ptr4 = (char*)ft_malloc(100);
    // char* ptr5 = (char*)ft_malloc(120);
    // char* ptr8 = (char*)ft_malloc(600);
    print_bins();
    
    ft_printf("\n\n");

        // ft_free(ptr7);

    char* ptr2 = (char*)ft_malloc(30);
        ft_free(ptr2);
    char* ptr300 = (char*)ft_malloc(300);
        ft_free(ptr300);
    char* ptr700 = (char*)ft_malloc(700);
        ft_free(ptr600);
        ft_free(ptr700);

        ft_free(ptr1);

    ft_printf("\n\n                 #### after free #####\n\n");
    print_bins();
}



int main() {

    // char *ptr = (char*)ft_calloc(8, 8);
    // ft_printf("ptr = %s\n", ptr);

    for (int i = 1; i <= 100; i++)
    {
        ft_malloc(TINY_BIN_MAX);
    }
    print_bins();
    print_arenas();

    return 0;
}


/*

*/