
#include "../inc/malloc.h"

/*
**  If there is not enough room to enlarge the memory allocation pointed to by ptr,
**  realloc() creates a new allocation, copies as much of the old data pointed to by ptr as will fit to
**  the new allocation, frees the old allocation, and returns a pointer to the allocated memory.
     
**  If ptr is NULL, realloc() is identical to a call to malloc() for size bytes.
    
**  If size is zero and ptr is not NULL, a new, minimum sized object is allocated and the original object is freed.
**
*/

void *my_realloc(void *ptr, size_t size) {
  if (!ptr || !global_arena)
    return ft_malloc(size);
  else if (size == 0) {
    ft_free(ptr);
    return NULL;
  }

  size = ALIGN8(size);

  t_bin *bin = (t_bin *)((char *)ptr - sizeof(t_bin));

  if (!is_within_the_heap(bin) || !is_magic_number_valid(bin))
    return NULL;

  if (size == bin->size)
    return ptr;

  if (size <= bin->size) {
    size_t copy_size = (size < bin->size) ? size : bin->size;
    void *new_ptr = ft_malloc(size);

    if (!new_ptr)
      return NULL;

    // ft_memmove(new_ptr, ptr, copy_size);
    ft_memcpy(new_ptr, ptr, copy_size);

    // Split the block if there is enough remaining space
    if (bin->size - size >= BIN_HEADER_SIZE) {
    //   t_bin *new_bin = (t_bin *)((char *)new_ptr - BIN_HEADER_SIZE);
    //   new_bin->size = bin->size - size - BIN_HEADER_SIZE;
    //   new_bin->is_free = 1;
         split_bin(bin, size);
    }

    

    ft_free(ptr);

    return new_ptr;
  }

  // Handle case where size > bin->size (no splitting)

  void *new_ptr = ft_malloc(size);
  if (!new_ptr)
    return NULL;

  size_t copy_size = (bin->size < size) ? bin->size : size;
//   ft_memmove(new_ptr, ptr, copy_size);
    ft_memcpy(new_ptr, ptr, copy_size);

  ft_free(ptr);

  return new_ptr;
}

/*

ft_memcpy(new_block, ptr, MIN(size, GET_L_BLOCK_SIZE(zone)));

*/