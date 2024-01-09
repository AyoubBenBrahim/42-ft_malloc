#include "inc/malloc.h"

int main()
{

	for (int i = 0; i < 100; i++)
    {
        char * ptr = (char *)malloc(100);
        ptr[0] = 42;
        // free(ptr);
    }

    // void * ptr2 = malloc(30);
    // void * ptr4 = malloc(300);

    // free(ptr1);
    // free(ptr2);
    // free(ptr4);

   show_alloc_mem();
}
