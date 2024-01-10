#include "../inc/malloc.h"
#include <stdio.h>
#include <stdlib.h>

t_bool is_magic_number_valid(t_bin *bin) {
  unsigned int expectedMagicNumber = generateMagicNumber(bin->parent_arena);
  if (bin->magic_number != expectedMagicNumber) {
    return FALSE;
  }
  return TRUE;
}

// Function to coalesce adjacent free bins (noun : coalescence)
t_bin *coalesce_adjacent_free_bins(t_bin *curr_free_bin) {
  t_bin *next_bin = curr_free_bin->next;
  t_bin *prev_bin = curr_free_bin->prev;
  t_bin *merged_bin = curr_free_bin;

  if (next_bin && next_bin->is_free) {
    // Coalesce with next bin
    curr_free_bin->size += BIN_HEADER_SIZE + next_bin->size;
    curr_free_bin->next = next_bin->next;
    if (next_bin->next)
      next_bin->next->prev = curr_free_bin;
  }

  if (prev_bin && prev_bin->is_free) {
    // Coalesce with previous bin
    prev_bin->size += BIN_HEADER_SIZE + curr_free_bin->size;
    prev_bin->next = curr_free_bin->next;
    if (curr_free_bin->next)
      curr_free_bin->next->prev = prev_bin;

    merged_bin = prev_bin;
  }

  return merged_bin;
}

void free_arena(t_bin *bin) {
  t_arena *arena = bin->parent_arena;

  if (g_arena == arena) {
    if (arena->next) {
      arena->next->tail = g_arena->tail;
      g_arena = arena->next;
    } else
      g_arena = NULL;
    
  } else if (g_arena->tail == arena) {
    g_arena->tail = arena->prev;
  }
  if (arena->prev) 
    arena->prev->next = arena->next;
  
  if (arena->next) {
    arena->next->prev = arena->prev;
  }

  int ret = munmap((void *)arena, arena->mapped_size);

  if (ret == -1) {
    return;
  }
}

t_bool free_tiny_small_bin(void *bin) {
  ((t_bin *)bin)->is_free = TRUE;
  ((t_bin *)bin)->magic_number = 0x1337;

  // handle free_size
  t_arena *arena = (t_arena *)(((t_bin *)bin)->parent_arena);
 
 // pre-existing bin, means it has already a BIN_HEADER_SIZE,
 // we still need it for future allocations
  arena->free_size += ((t_bin *)bin)->size; 

  return TRUE;
}

void my_free(void *ptr) {

  t_bin *bin = (t_bin *)((char *)ptr - sizeof(t_bin));

  if (!is_magic_number_valid(bin)) {
    return;
  }

  t_bins_type bin_type = get_bins_type(bin->size);

  if (bin_type == LARGE) {
    bin->is_free = TRUE;
    bin->magic_number = 0x1337;
    free_arena(bin);
    return;
  }

  free_tiny_small_bin(bin);

  t_bin *merged_bin = coalesce_adjacent_free_bins(bin);

  if (merged_bin && merged_bin->next == NULL) {
    // Update the tail bin in the arena
    set_last_bin_in_arena(merged_bin);
  }

  if (merged_bin && !merged_bin->next && !merged_bin->prev) {
    // If the bin is the last bin in the arena, check if the arena is empty
    free_arena(merged_bin);
    return;
  }
}

void free(void* ptr) {
    pthread_mutex_lock(&g_mallocMutex);
    my_free(ptr);
    pthread_mutex_unlock(&g_mallocMutex);
}