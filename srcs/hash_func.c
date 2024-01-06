#include "../inc/malloc.h"

unsigned int generateMagicNumber(t_arena *parent_arena) {
    uintptr_t ptr = (uintptr_t)parent_arena;

    char *binaryStr = to_binary(ptr);
    unsigned int hash = 2166136261U;

    for (size_t i = 0; i < strlen(binaryStr); i++) {
        hash ^= binaryStr[i];
        hash *= 16777619;
    }

    return hash;
}