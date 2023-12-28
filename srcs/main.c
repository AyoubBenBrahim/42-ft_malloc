#include "../inc/malloc.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void test_large_bin()
{
    char* ptr = (char*)my_malloc(200);
    char* ptr2 = (char*)my_malloc(200);
    char* ptr3 = (char*)my_malloc(200);
    char* ptr4 = (char*)my_malloc(700);
    char* ptr5 = (char*)my_malloc(600);
    
    print_bins();
    
    ft_printf("\n\n");

    ft_printf("ret_ptr1 = %p\n", ptr);
    ft_printf("ret_ptr2 = %p\n", ptr2);
    ft_printf("ret_ptr3 = %p\n", ptr3);
    ft_printf("--------------------\n");

    my_free(ptr);
    ft_printf("--------------------\n");
    my_free(ptr2);
    ft_printf("--------------------\n");
    my_free(ptr3);
    ft_printf("--------------------\n");
    my_free(ptr4);

    ft_printf("\n\n                 #### after free #####\n\n");
    print_bins();
}

void test_tiny_bin()
{
    char* ptr1 = (char*)ft_malloc(10);
    char* ptr2 = (char*)ft_malloc(30);
    // char* ptr3 = (char*)ft_malloc(60);
    // char* ptr4 = (char*)ft_malloc(100);
    // char* ptr5 = (char*)ft_malloc(120);
    char* ptr7 = (char*)ft_malloc(300);
    char* ptr8 = (char*)ft_malloc(600);
    print_bins();
    
    ft_printf("\n\n");

    // ft_printf("ret_ptr1 = %p\n", ptr1);
    // ft_printf("ret_ptr2 = %p\n", ptr2);
    // ft_printf("ret_ptr3 = %p\n", ptr3);
    // ft_printf("ret_ptr4 = %p\n", ptr4);
    // ft_printf("ret_ptr5 = %p\n", ptr5);
    ft_printf("--------------------\n");

    // ft_free(ptr);
    // ft_printf("--------------------\n");
    // ft_free(ptr2);
    // ft_printf("--------------------\n");
    // ft_free(ptr3);
    // ft_printf("--------------------\n");
        ft_free(ptr1);
        ft_free(ptr7);
        ft_free(ptr2);
        // char* ptr10 = (char*)ft_malloc(60);
    // ft_free(ptr3);
    // ft_free(ptr4);
    ft_printf("test double free------>>\n");
    ft_free(ptr2);
    ft_free(ptr8);

    ft_printf("\n\n                 #### after free #####\n\n");
    print_bins();
}

void test()
{
    t_bin *bin = (t_bin*)malloc(sizeof(t_bin));
    ft_printf(" sizeof(t_bin)              = %zu\n", sizeof(t_bin));                // 40
    ft_printf(" bin                        = %p\n", bin);                          // 0x7ff968c05950
    ft_printf("(void *)bin                 = %p\n", (void *)bin);                  // 0x7ff968c05950

    ft_printf("(void *)bin+1               = %p\n", (void *)bin + 1);              // 0x7ff968c05951

    ft_printf("bin+sizeof(t_bin)           = %p\n", bin + sizeof(t_bin));          // 0x7fb4e1c05f90 
    // incorrect to add sizeof(t_bin) directly to the pointer. 

    ft_printf(" bin + 1                    = %p\n", bin + 1);                      // 0x7ff968c05978
    // adds 1 to the pointer bin <=> sizeof(t_bin) * 1

     ft_printf(" (t_bin *)(bin + 1)        = %p\n", (t_bin *)(bin + 1));           // 0x7ff968c05978

    ft_printf("(void *)bin+sizeof(t_bin)   = %p\n", (void *)bin+sizeof(t_bin));    // 0x7ff968c05978
    ft_printf("(char *)bin + sizeof        = %p\n", (char *)bin + sizeof(t_bin) ); // 0x7ff968c05978 

    ft_printf("(t_bin *)((void *)bin + sizeof  )      = %p\n", (t_bin *)((void *)bin + sizeof(t_bin)) ); // 0x7ff968c05978

    ft_printf("(void *)((void *)best_fit + sizeof(t_bin)) = %p\n", (void *)((void *)bin + sizeof(t_bin))); // 0x7ff968c05978
    exit(0);
}

int main() {


    // for (int i = 10; i < 15; i++)
    // {
    //     my_malloc(i);
    //     // print_arenas(128);
    // }

    
    test_tiny_bin();

  exit(0);
    // LARGE BIN
    test_large_bin();

    return 0;
}


/*
 




*/