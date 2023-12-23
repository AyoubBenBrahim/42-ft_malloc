#include "../inc/malloc.h"
#include <string.h>

// void init_arena() {
//     main_arena->tiny_bins = NULL;
//     main_arena->small_bins = NULL;
//     main_arena->large_bins = NULL;
// }

int main() {
    // init_arena();
    char* ptr = (char*)my_malloc(10);
    // ptr[0] = 'H';
    // ptr[1] = 'e';
    // ptr[2] = 'l';
    // ptr[3] = 'l';
    // ptr[4] = 'o';
    // ptr[5] = '\0';

    memset(ptr, 'A', 10);

    printf(" p = %p\n", &ptr);
    printf("%s\n", ptr);
    // free(ptr);
    return 0;
}