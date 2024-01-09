#include "../inc/malloc.h"

/*
** If the pointer passed to realloc is NULL, it behaves like malloc and
** allocates a new memory block of the given size.
**
** If the size passed to realloc is zero -and ptr is not NULL,-, it behaves like
** free and deallocates the memory block pointed to by the pointer.

**  If there is not enough room to enlarge the memory allocation pointed to by ptr,
**  realloc() creates a new allocation, copies as much of the old data pointed
**  to by ptr as will fit to
**  the new allocation, frees the old allocation, and returns a pointer to the
** allocated memory.
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

t_bool realloc_split_bin(t_bin *bin, size_t size) {
  t_bin *new_free_bin = (t_bin *)((void *)bin + BIN_HEADER_SIZE + size); // bin [      size|        bin_size]

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

  return TRUE;
}

void expand_bin(t_bin *curr_bin) {
  t_bin *next_bin = curr_bin->next;

  if (next_bin && next_bin->is_free) {
    // join with next bin
    curr_bin->size += BIN_HEADER_SIZE + next_bin->size;
    curr_bin->next = next_bin->next;
    if (next_bin->next)
      next_bin->next->prev = curr_bin;
  }
}

void *my_realloc(void *ptr, size_t size) {
  if (!ptr || !g_arena)
    return my_malloc(size);
  else if (size == 0) {
    my_free(ptr);
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
    // (bin->size > size + BIN_HEADER_SIZE) same as
    if (bin->size - size >= BIN_HEADER_SIZE) {
      realloc_split_bin(bin, size);
    }
    return ptr;
  }

  // Handle case where size > bin->size (no splitting)

  // Try to extend the block if possible
  if (bin->next && bin->next->is_free &&
      (bin->size + BIN_HEADER_SIZE + bin->next->size) >= size) {
    expand_bin(bin);
    if (bin->size - size >= BIN_HEADER_SIZE) {
      realloc_split_bin(bin, size);
    }
    return ptr;
  }

  void *new_ptr = my_malloc(size);

  if (!new_ptr)
    return NULL;

  ft_memcpy(new_ptr, ptr, bin->size);

  my_free(ptr);

  return new_ptr;
}

void    *realloc(void *ptr, size_t size){
    pthread_mutex_lock(&g_mallocMutex);
    void* new_ptr = my_realloc(ptr, size);
    pthread_mutex_unlock(&g_mallocMutex);
    return new_ptr;
}