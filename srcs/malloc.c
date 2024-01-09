#include "../inc/malloc.h"

pthread_mutex_t g_mallocMutex = PTHREAD_MUTEX_INITIALIZER;
t_arena *g_arena = NULL;

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
   size = ALIGN8(size);

  t_bins_type bins_type = get_bins_type(size);

  if (bins_type == LARGE) {
    t_bin *new_bin = create_new_arena(bins_type, size);
    return (new_bin) ? (void *)(new_bin + 1) : NULL;
  }

  // Find the best-fit TINY or SMALL
  t_bin *best_fit = find_best_fit(bins_type, size);

  // If a suitable bin is found, allocate from it
  if (best_fit)
    return (void *)((void *)best_fit + BIN_HEADER_SIZE);

  // If no suitable bin is found, allocate a new arena via mmap()
  t_bin *new_bin = create_new_arena(bins_type, size);

  return (new_bin) ? (void *)(new_bin + 1) : NULL;
}

void    *ft_malloc(size_t size) {
    pthread_mutex_lock(&g_mallocMutex);
    void* ptr = my_malloc(size);
    pthread_mutex_unlock(&g_mallocMutex);
    return ptr;
}