
#include "../inc/malloc.h"

t_bin *create_new_arena(t_bins_type bins_type, size_t size) {

  t_arena *new_arena = request_new_page_mmap(bins_type, GET_BIN_SIZE(bins_type));
  if (!new_arena)
    return NULL;

  new_arena->next = NULL;
  new_arena->bin_type = bins_type;
  new_arena->free_size = GET_BIN_SIZE(bins_type) - METADATA_SIZE(size); // recheck

  t_bin *new_bin = (t_bin *)(new_arena + 1); // (void *)new_arena+sizeof(t_arena)

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

  return new_bin;
}