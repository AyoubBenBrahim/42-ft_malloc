#include "../inc/malloc.h"
#include <stdio.h>

int main() {

    for (int i = 1; i <= 100; i++) {
      char * ptr1 = (char *)ft_malloc(10);
      char * ptr2 = (char *)ft_malloc(30);
      char * ptr3 = (char *)ft_malloc(3000);

      ptr1[0] = 'A';
    ptr2[1] = 'B';
    ptr3[2] = 'C';
    }


     // ptr4 = ft_realloc(ptr4, 120);


    //     ft_free(ptr1);
    //     ft_free(ptr2);


     // void *  ptr1 = malloc(50);
    //   void *  ptr2 = malloc(70);
   
    // }

    // char * ptr1 = (char *)ft_malloc(10);
    // char * ptr2 = (char *)ft_malloc(30);
    // char * ptr3 = (char *)ft_malloc(300);
    // // char * ptr4 = (char *)ft_malloc(3000000000000);
    // ptr1[0] = 'A';
    // ptr2[1] = 'B';
    // ptr3[2] = 'C';
    

   
    // ft_free(ptr1);
    // ft_free(ptr2);
    // ft_free(ptr3);
    // ft_free(ptr4);

    show_alloc_mem();

    // print_bins();
    // print_arenas();

//size_t size = atoi(argv[1]);
  

//size_t size_8 = ALIGN8(size);
// size_t size_16 = ROUND_TO_MULTIPLE_OF_16(size);

//printf("size_8: %zu\n", size_8);
//printf("size_16 %zu\n", size_16);

    return 0;
}

