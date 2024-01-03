#include "../../inc/malloc.h"

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