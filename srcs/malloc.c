#include "../inc/malloc.h"

void print_arena()
{
  t_arena *current = global_arena;
  while (current)
  {
    printf("arena = %p\n", current);
    printf("arena->last = %p\n", current->last);
    int bins_type = current->bin_type;

    if (bins_type == TINY)
      printf("arena->bin_type = TINY\n");
    else if (bins_type == SMALL)
      printf("arena->bin_type = SMALL\n");
    else
      printf("arena->bin_type = LARGE\n");

    printf("arena->nbr_bins = %zu\n", current->allocated_bins_count);

    printf("arena->free_size = %zu\n", current->free_size);
    printf("\n");
    current = current->next;
  }
  printf("===============================================\n");
}

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
    return (void *)((void *)best_fit + BIN_HEADER_SIZE);
  }

  // If no suitable bin is found, allocate a new block using mmap()
  t_arena *new_arena = (t_arena *)request_new_page_mmap(bins_type, GET_BIN_SIZE(bins_type));
  if (!new_arena)
    return NULL;
    
  new_arena->next = NULL;
  new_arena->bin_type = bins_type;
  new_arena->free_size = GET_BIN_SIZE(bins_type) - METADATA_SIZE(size); // recheck

  t_bin *new_bin = (t_bin *)(new_arena + 1);

  new_bin->size = size;
  new_bin->next = NULL;
  new_bin->prev = NULL;
  new_bin->is_free = FALSE;
  new_arena->allocated_bins_count = 1;

  set_last_bin(&new_arena, bins_type, new_bin);
  // Add the new arena to the list of arenas

  if (!global_arena) {
    ASSERT(global_arena == NULL);

    global_arena = new_arena;
    global_arena->last = new_arena;

    global_arena->last_tiny_bin = NULL;
    global_arena->last_small_bin = NULL;

  } else {
    ASSERT(global_arena != NULL);
 
    global_arena->last->next = new_arena;
    global_arena->last = new_arena;
  }

  

  return (void *)(new_bin + 1);
}
