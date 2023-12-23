
#include "../inc/malloc.h"

void *handle_large_bins(t_bins_type bins_type, size_t size)
{
     t_arena* new_arena = request_new_page_mmap(LARGE, METADATA_SIZE(size)); 
        if (!new_arena)
            return NULL;
        new_arena->next = NULL;
        new_arena->bin_type = LARGE;
        new_arena->free_size = 0;
        // new_arena->is_full = TRUE;
        if (!global_arena) {
            global_arena->last = new_arena;
            global_arena = new_arena;
            return (void*)((void*)new_arena + ARENA_STRUCT_SIZE);
        }
        global_arena->last->next = new_arena;
        global_arena->last = new_arena;
        return (void*)((void*)new_arena + ARENA_STRUCT_SIZE);
}
