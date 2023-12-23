
#include "../inc/malloc.h"

void *handle_large_bins(size_t size) {
     t_arena* new_arena = request_new_page_mmap(LARGE, size);
        if (!new_arena)
            return NULL;
        new_arena->next = NULL;
        new_arena->bin_type = LARGE;
        new_arena->free_size = 0;
        new_arena->is_full = TRUE;
        if (!global_arena) {
            global_arena->last = new_arena;
            global_arena = new_arena;
            return (void*)((char*)new_arena + METADATA_SIZE(size));
        }
        global_arena->last->next = new_arena;
        return (void*)((char*)new_arena + METADATA_SIZE(size));
}
