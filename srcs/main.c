#include "../inc/malloc.h"
#include <string.h>

// void init_arena() {
//     main_arena->tiny_bins = NULL;
//     main_arena->small_bins = NULL;
//     main_arena->large_bins = NULL;
// }

int main() {
    // init_arena();
    // char* ptr = (char*)my_malloc(10);

   for (int i = 1; i < 50; i++)
   {
        char* ptr = (char*)my_malloc(i);
        memset(ptr, 'A', i);
        printf(" p = %p\n", &ptr);
   }

    // memset(ptr, 'B', 10);

    // printf(" p = %p\n", &ptr);
    // printf("%s\n", ptr);
    // free(ptr);
    return 0;
}