
#include "../inc/malloc.h"

/*

** If the pointer passed to realloc is NULL, it behaves like malloc and allocates a new memory block of the given size.
** If the size passed to realloc is zero, it behaves like free and deallocates the memory block pointed to by the pointer.


**  If there is not enough room to enlarge the memory allocation pointed to by ptr,
**  realloc() creates a new allocation, copies as much of the old data pointed to by ptr as will fit to
**  the new allocation, frees the old allocation, and returns a pointer to the allocated memory.
     
**  If ptr is NULL, realloc() is identical to a call to malloc() for size bytes.
    
**  If size is zero and ptr is not NULL, a new, minimum sized object is allocated and the original object is freed.
**
*/

void ft_set_last_bin_in_arena(t_bin *bin) {
    t_arena *arena = bin->parent_arena;
    t_bins_type binType = arena->bin_type;
    if (binType == TINY) {
        arena->last_tiny_bin = bin;
    } else if (binType == SMALL) {
        arena->last_small_bin = bin;
    }
}

t_bool realloc_split_bin(t_bin* bin, size_t size)
{    
    t_bin* new_free_bin = (t_bin*)((void*)bin + BIN_HEADER_SIZE + size);// bin [      size|        bin_size]     

    new_free_bin->size = bin->size - size - BIN_HEADER_SIZE;           
    new_free_bin->next = bin->next;
    new_free_bin->prev = bin;
    new_free_bin->is_free = TRUE;
    new_free_bin->parent_arena = bin->parent_arena;

    bin->size = size;
    bin->next = new_free_bin;
    bin->is_free = FALSE;

    if (new_free_bin->next)
        new_free_bin->next->prev = new_free_bin;

    if (new_free_bin->next == NULL)
        ft_set_last_bin_in_arena(new_free_bin);

    new_free_bin->magic_number = 1337;

    bin->parent_arena->free_size -= BIN_HEADER_SIZE;

    return  TRUE;
}

void expand_bin(t_bin* curr_bin) {
    t_arena* arena = (t_arena*)((char*)curr_bin->parent_arena);
    t_bin* next_bin = curr_bin->next;

    if (next_bin && next_bin->is_free) {
        // join with next bin
        curr_bin->size += BIN_HEADER_SIZE + next_bin->size;
        curr_bin->next = next_bin->next;
        if (next_bin->next)
            next_bin->next->prev = curr_bin;
    }
}

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
    // Split the block if there is enough remaining space
    if (bin->size - size >= BIN_HEADER_SIZE) {
         realloc_split_bin(bin, size);
    }
    return ptr;
  }

  // Handle case where size > bin->size (no splitting)

  // Try to extend the block if possible
  if (bin->next && bin->next->is_free && (bin->size + BIN_HEADER_SIZE + bin->next->size) >= size) {
    expand_bin(bin);
    if (bin->size - size >= BIN_HEADER_SIZE) {
         realloc_split_bin(bin, size);
    }
    return ptr;
  }

  void *new_ptr = ft_malloc(size);

  if (!new_ptr)
    return NULL;

//   ft_memmove(new_ptr, ptr, copy_size);

  ft_memcpy(new_ptr, ptr, bin->size);

  ft_free(ptr);

  return new_ptr;
}

/*

ft_memcpy(new_block, ptr, MIN(size, GET_L_BLOCK_SIZE(zone)));

*/

// void *realloc(void *p, size_t size) {
//   size_t s;
//   t_block b, new;
//   void *newp;
//   if (!p)
//     return (malloc(size));
//   if (valid_addr(p)) 
//   {
//     s = align4(size);
//     b = get_block(p);
//     if (b->size >= s) 
//     {
//          if (b->size - s >= (BLOCK_SIZE + 4))
//            split_block(b, s);
//     } else 
//     {
//          /* Try fusion with next if possible */
//          if (b->next && b->next->free && (b->size + BLOCK_SIZE + b->next->size) >= s) 
//         {
//            fusion(b);
//            if (b->size - s >= (BLOCK_SIZE + 4))
//              split_block(b, s);
//          } else 
//          {
//            /* good old realloc with a new block */
//            newp = malloc(s);
//            if (!newp)
//              /* we’re doomed ! */
//              return (NULL);
//            /* I assume this work ! */
//            new = get_block(newp);
//            /* Copy data */
//            copy_block(b, new);
//            /* free the old one */
//            free(p);
//            return (newp);
//          }
//     }
//     return (p);
//   }
//   return (NULL);
// }
