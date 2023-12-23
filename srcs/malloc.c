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
  size = ALIGN8(size); // + sizeof(t_bin); already added

  t_bins_type bins_type = get_bins_type(size);

  if (bins_type == LARGE) {
    return  handle_large_bins(bins_type, size);
  }

  // Find the best-fit block for large allocations


  t_bin *best_fit = find_best_fit(bins_type, size);

  // If a suitable bin is found, allocate from it
  if (best_fit) {
    // Split the bin if it is large enough
    ASSERT(best_fit != NULL);
    if (best_fit->size >= size + sizeof(t_bin))
    {
      ASSERT(best_fit->size >= size + sizeof(t_bin));
      split_bin(best_fit, size);
    }

    // best_fit->is_free = FALSE;
    
    return (void *)((void *)best_fit + sizeof(t_bin));
  }

  // If no suitable bin is found, allocate a new block using mmap()
  t_arena *new_arena = (t_arena *)request_new_page_mmap(bins_type, GET_BIN_SIZE(bins_type));
  if (!new_arena)
    return NULL;

  new_arena->next = NULL;
  // new_arena->last = new_arena;
  new_arena->bin_type = bins_type;
  // new_arena->is_full = FALSE;
  new_arena->free_size = GET_BIN_SIZE(bins_type) - METADATA_SIZE(size); // recheck

  t_bin *new_bin = (t_bin *)((void *)new_arena + sizeof(t_arena));
  new_bin->size = size;
  new_bin->next = NULL;
  new_bin->is_free = FALSE;

  // Add the new arena to the list of arenas
  if (!global_arena) {
    ASSERT(global_arena == NULL);
    global_arena = new_arena;
    global_arena->last = new_arena;
  } else {
    ASSERT(global_arena != NULL);
    // t_arena* current = global_arena;
    // while (current->next)
    //     current = current->next;
    // current->next = new_arena;
    global_arena->last->next = new_arena;
    global_arena->last = new_arena;
  }

  return (void *)((char *)new_bin + sizeof(t_bin));
}
