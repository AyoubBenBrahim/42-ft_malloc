#include "../inc/malloc.h"

t_bins_type get_bins_type(size_t size) {
  if (IS_TINY(size))
    return TINY;
  else if (IS_SMALL(size))
    return SMALL;
  else
    return LARGE;
}

void *my_malloc(size_t size) {
  if (size <= 0)
    return NULL;

  // Align the size to the nearest multiple of the page size
  // size = align_size(size);
  size = ALIGN4(size) + sizeof(t_bin);

  t_bins_type bins_type = get_bins_type(size);

  if (bins_type == LARGE) {
    return request_new_page_mmap(bins_type, size);
  }

  // Find the best-fit block for large allocations

  t_arena *arenaa = NULL;
  t_bin *best_fit = find_best_fit(bins_type, size, &arenaa);

  // If a suitable bin is found, allocate from it
  if (best_fit) {
    // Split the bin if it is large enough
    if (best_fit->size >= size + sizeof(t_bin))
      split_bin(best_fit, size);

    best_fit->is_free = FALSE;
    
    return (void *)((void *)best_fit + sizeof(t_bin));
  }

  // If no suitable block is found, allocate a new block using mmap()
  t_arena *new_arena = (t_arena *)request_new_page_mmap(bins_type, size);
  if (!new_arena)
    return NULL;

  new_arena->next = NULL;
  new_arena->last = new_arena;
  new_arena->bin_type = bins_type;
  new_arena->is_full = FALSE;
  new_arena->free_size = size - sizeof(t_arena) - sizeof(t_bin); // recheck

  t_bin *new_bin = (t_bin *)((char *)new_arena + sizeof(t_arena));
  new_bin->size = size;
  new_bin->next = NULL;
  new_bin->is_free = FALSE;

  // Add the new arena to the list of arenas
  if (!global_arena) {
    global_arena = new_arena;
  } else {
    // t_arena* current = global_arena;
    // while (current->next)
    //     current = current->next;
    // current->next = new_arena;
    global_arena->last->next = new_arena;
    global_arena->last = new_arena;
  }

  return (void *)((char *)new_bin + sizeof(t_bin));
}
