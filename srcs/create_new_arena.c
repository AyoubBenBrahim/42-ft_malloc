
#include "../inc/malloc.h"

t_bin *create_new_arena(t_bins_type bins_type, size_t size) {

  t_arena *new_arena = request_new_page_mmap(bins_type, GET_BIN_SIZE(bins_type));
  if (!new_arena)
    return NULL;

  new_arena->next = NULL;
  new_arena->prev = NULL;
  new_arena->bin_type = bins_type;
  new_arena->allocated_bins_count = 1;
  new_arena->mapped_size = GET_BIN_SIZE(bins_type);
  new_arena->free_size = new_arena->mapped_size - METADATA_SIZE(size); // recheck
  // new_arena->tail = new_arena;

  t_bin *new_bin = (t_bin *)(new_arena + 1); // (void *)new_arena+sizeof(t_arena)

  ft_printf("sizeof(t_arena) = %zu = 0x%lx\n", sizeof(t_arena), sizeof(t_arena));
  ft_printf("sizeof(t_bin) = %zu = 0x%lx \n", sizeof(t_bin), sizeof(t_bin));
  ft_printf("arena = %p\n", new_arena);
  ft_printf(" new_bin = %p\n", new_bin);

  new_bin->size = size;
  new_bin->next = NULL;
  new_bin->prev = NULL;
  new_bin->is_free = FALSE;
  new_bin->parent_arena = new_arena; //;(global_arena == NULL) ? new_arena : global_arena;

  set_last_bin_in_arena(new_bin);
  // Add the new arena to the list of arenas

  if (!global_arena) {
    ASSERT(global_arena == NULL);

    global_arena = new_arena;
    global_arena->tail = new_arena;

  } else {
    ASSERT(global_arena != NULL);

    new_arena->prev = global_arena->tail;
    global_arena->tail->next = new_arena;
    global_arena->tail = new_arena;
  }

  new_bin->magic_number = generateMagicNumber(new_bin->parent_arena);

  return new_bin;
}