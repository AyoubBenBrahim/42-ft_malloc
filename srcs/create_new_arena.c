#include "../inc/malloc.h"

t_bin *create_new_arena(t_bins_type bins_type, size_t size) {

  size_t arena_size = (bins_type == LARGE) ? METADATA_SIZE(size) : GET_BIN_SIZE(bins_type);
  t_arena *new_arena = request_new_page_mmap(arena_size);
  if (!new_arena)
    return NULL;

  new_arena->next = NULL;
  new_arena->prev = NULL;
  new_arena->bin_type = bins_type;
  new_arena->mapped_size = arena_size;
  new_arena->free_size = new_arena->mapped_size - METADATA_SIZE(size);

  t_bin *new_bin = (t_bin *)(new_arena + 1);

  new_bin->size = size;
  new_bin->next = NULL;
  new_bin->prev = NULL;
  new_bin->is_free = FALSE;
  new_bin->parent_arena = new_arena;
  new_bin->magic_number = generateMagicNumber(new_bin->parent_arena);

  set_last_bin_in_arena(new_bin);

  // Add the new arena to the list of arenas

  if (!g_arena) {
    ASSERT(g_arena == NULL);

    g_arena = new_arena;
    g_arena->tail = new_arena;

  } else {
    ASSERT(g_arena != NULL);

    new_arena->prev = g_arena->tail;
    g_arena->tail->next = new_arena;
    g_arena->tail = new_arena;
  }
  return new_bin;
}