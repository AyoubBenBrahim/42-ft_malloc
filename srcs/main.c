#include "../inc/malloc.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


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

//******


//******


int main() {
	
    ft_malloc(10);
    ft_malloc(30);
    ft_malloc(600);
    ft_malloc(300);
    ft_malloc(2000);

    show_alloc_mem();

    // print_bins();
    // print_arenas();

    return 0;
}

