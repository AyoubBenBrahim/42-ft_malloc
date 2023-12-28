
#include "../inc/malloc.h"

void *handle_large_bins(t_bins_type bins_type, size_t size)
{
     t_arena* new_arena = request_new_page_mmap(LARGE, METADATA_SIZE(size)); 
        if (!new_arena)
            return NULL;
        new_arena->next = NULL;
        new_arena->bin_type = LARGE;
        new_arena->mapped_size = METADATA_SIZE(size);
        new_arena->free_size = 0;
        new_arena->allocated_bins_count = 1;
        

        t_bin *new_bin = (t_bin *)(new_arena + 1); // (void *)new_arena+sizeof(t_arena)

        new_bin->size = size;
        new_bin->next = NULL;
        new_bin->prev = NULL;
        new_bin->is_free = FALSE;
        new_bin->parent_arena = new_arena; 

        if (!global_arena) {
            global_arena->tail = new_arena;
            global_arena = new_arena;
        }
        else {
            new_arena->prev = global_arena->tail;
            global_arena->tail->next = new_arena;
            global_arena->tail = new_arena;
        }
        // return (void*)((void*)new_arena + ARENA_HEADER_SIZE);
        // return (void*)((void*)new_bin + BIN_HEADER_SIZE);
        new_bin->magic_number = generateMagicNumber(new_bin->parent_arena);
        ft_printf("LARGE new_bin->magic_number = %u\n", new_bin->magic_number);
        return new_bin;
}
