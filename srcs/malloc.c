#include "../inc/malloc.h"
#include <stddef.h>
#include <stdlib.h>

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
  // size_t size_orig = size;
  size = ALIGN8(size); // + sizeof(t_bin); already added

  t_bins_type bins_type = get_bins_type(size);

  char *bin_type_str = (bins_type == TINY) ? "TINY" : (bins_type == SMALL) ? "SMALL" : "LARGE";
  
  // ft_printf("SMALL_BIN_SIZE = %zu\n", SMALL_BIN_SIZE);
  // ft_printf("size = %zu\n", size);
  // ft_printf("bin_type = %s\n", bin_type_str);
  // exit(0);

  if (bins_type == LARGE)
  {
    t_bin *new_bin =  create_new_arena(bins_type, size);
    return (new_bin) ? (void *)(new_bin + 1) : NULL;
  }

  // Find the best-fit block TINY or SMALL
  t_bin *best_fit = find_best_fit(bins_type, size);

  // If a suitable bin is found, allocate from it
  if (best_fit)
    return (void *)((void *)best_fit + BIN_HEADER_SIZE);

  // If no suitable bin is found, allocate a new arena via mmap()
  t_bin *new_bin = create_new_arena(bins_type, size);

  return (new_bin) ? (void *)(new_bin + 1) : NULL;
}
