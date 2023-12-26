#include "../inc/malloc.h"
#include <stdio.h>
#include <sys/_types/_uintptr_t.h>


unsigned int generateMagicNumber() {
    uintptr_t ptr = (uintptr_t)global_arena;
    // void *ptr = (void *)global_arena;
    size_t size = sizeof(ptr);

    // ft_printf("uintptr_t ptr = %p\n", (void *)ptr);

    char *binaryStr = to_binary(ptr);
    // ft_printf("binaryStr = %s\n", binaryStr);

    unsigned int hash = 2166136261U;

    for (size_t i = 0; i < strlen(binaryStr); i++) {
        hash ^= binaryStr[i];
        hash *= 16777619;
    }

    return hash;
}

// int main() {
//     unsigned int magicNumber = generateMagicNumber();
//     ft_printf("magicNumber = %u\n", magicNumber);
//     // uintptr_t ptr = 0x10b9b5000;
//     // // char *test = to_binary(ptr);
//     // ft_printf("%s\n", test);

//     return 0;
// }