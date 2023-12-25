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

//    test();

    // init_arena();
    // char* ptr = (char*)my_malloc(10);

//    for (int i = 1; i < 50; i++)
//    {
//         char* ptr = (char*)my_malloc(i);
//         memset(ptr, 'A', i);
//         printf(" p = %p\n", &ptr);
//         ptr = NULL;
//    }



    for (int i = 0; i < 100; i++)
    {
        my_malloc(128);
        print_arena(128);
    }

    my_malloc(100);
    print_arena(100);

    for (int i = 0; i < 101; i++)
    {
        my_malloc(512);
        print_arena(512);
    }

    my_malloc(600);
    print_arena(600);
  



    return 0;
}

/*
 




*/