#include "../inc/malloc.h"
#include <stdio.h>
#include <stdlib.h>

void test()
{
    t_bin *bin = (t_bin*)malloc(sizeof(t_bin));
    printf(" sizeof(t_bin)              = %zu\n", sizeof(t_bin));                // 40
    printf(" bin                        = %p\n", bin);                          // 0x7ff968c05950
    printf("(void *)bin                 = %p\n", (void *)bin);                  // 0x7ff968c05950

    printf("(void *)bin+1               = %p\n", (void *)bin + 1);              // 0x7ff968c05951

    printf("bin+sizeof(t_bin)           = %p\n", bin + sizeof(t_bin));          // 0x7fb4e1c05f90 
    // incorrect to add sizeof(t_bin) directly to the pointer. 

    printf(" bin + 1                    = %p\n", bin + 1);                      // 0x7ff968c05978
    // adds 1 to the pointer bin <=> sizeof(t_bin) * 1

     printf(" (t_bin *)(bin + 1)        = %p\n", (t_bin *)(bin + 1));           // 0x7ff968c05978

    printf("(void *)bin+sizeof(t_bin)   = %p\n", (void *)bin+sizeof(t_bin));    // 0x7ff968c05978
    printf("(char *)bin + sizeof        = %p\n", (char *)bin + sizeof(t_bin) ); // 0x7ff968c05978 

    printf("(t_bin *)((void *)bin + sizeof  )      = %p\n", (t_bin *)((void *)bin + sizeof(t_bin)) ); // 0x7ff968c05978

    printf("(void *)((void *)best_fit + sizeof(t_bin)) = %p\n", (void *)((void *)bin + sizeof(t_bin))); // 0x7ff968c05978
    exit(0);
}

int main() {

   test();

    // init_arena();
    // char* ptr = (char*)my_malloc(10);

//    for (int i = 1; i < 50; i++)
//    {
//         char* ptr = (char*)my_malloc(i);
//         memset(ptr, 'A', i);
//         printf(" p = %p\n", &ptr);
//         ptr = NULL;
//    }

    // memset(ptr, 'B', 10);

    // printf(" p = %p\n", &ptr);
    // printf("%s\n", ptr);
    // free(ptr);

    // char* ptr1 = (char*)my_malloc(10);
    // char* ptr2 = (char*)my_malloc(20);
    // char* ptr3 = (char*)my_malloc(30);
    // char* ptr4 = (char*)my_malloc(50);
    // char* ptr5 = (char*)my_malloc(60);
    // char* ptr6 = (char*)my_malloc(80);
    // char* ptr7 = (char*)my_malloc(100);
    // char* ptr8 = (char*)my_malloc(120);
    // char* ptr9 = (char*)my_malloc(150);
    // char* ptr10 = (char*)my_malloc(220);

    // printf(" p1 = %p\n", &ptr1);
    // printf(" p2 = %p\n", &ptr2);
    // printf(" p3 = %p\n", &ptr3);
    // printf(" p4 = %p\n", &ptr4);
    // printf(" p5 = %p\n", &ptr5);
    // printf(" p6 = %p\n", &ptr6);
    // printf(" p7 = %p\n", &ptr7);
    // printf(" p8 = %p\n", &ptr8);
    // printf(" p9 = %p\n", &ptr9);
    // printf(" p10 = %p\n", &ptr10);

    // char* ptr1 = (char*)my_malloc(900);
    // char* ptr2 = (char*)my_malloc(900);
    // char* ptr3 = (char*)my_malloc(900);
    // char* ptr4 = (char*)my_malloc(900);

    // printf(" p1 = %p\n", &ptr1);
    // printf(" p2 = %p\n", &ptr2);
    // printf(" p3 = %p\n", &ptr3);
    // printf(" p4 = %p\n", &ptr4);

    // char* ptr100 = (char*)my_malloc(1000);
    // print_arena();
    // char* ptr10 = (char*)my_malloc(1000);
    // print_arena();
    // char* ptr1 = (char*)my_malloc(10);
    // print_arena();
    // char* ptr2 = (char*)my_malloc(20);
    // print_arena();
    // char* ptr3 = (char*)my_malloc(1000);
    // print_arena();


    // char* ptr200 = (char*)my_malloc(4*4096);
    // print_arena();
    // char* ptr300 = (char*)my_malloc(4*4096+10);
    // print_arena();
    // char* ptr400 = (char*)my_malloc(32*4096);
    // print_arena();
    // char* ptr500 = (char*)my_malloc(4*4096+10);

    // sizeof(t_arena) + sizeof(t_bin)
    char* ptr1 = (char*)my_malloc(1);
    print_arena();
    // sizeof(t_arena) + sizeof(t_bin) + 1 + sizeof(t_bin)
    char* ptr2 = (char*)my_malloc(1);
    print_arena();
    // sizeof(t_arena) + sizeof(t_bin) + 1 + sizeof(t_bin) + 1 + sizeof(t_bin)
    char* ptr3 = (char*)my_malloc(1);
    print_arena();


    printf(" p1 = %p\n", &ptr1);
    printf(" p2 = %p\n", &ptr2);
    printf(" p3 = %p\n", &ptr3);
    // printf(" p4 = %p\n", &ptr400);
    // printf(" p5 = %p\n", &ptr500);


    return 0;
}

/*
 p mem
(void *) $12 = 0x0000000100134000

p new_arena 
(t_arena *) $14 = 0x0000000100134000




*/