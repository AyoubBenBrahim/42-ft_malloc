
#include "../inc/malloc.h"
#include <stddef.h>
#include <stdlib.h>
#include <sys/mman.h>

t_bool is_within_the_heap(void *ptr)
{
    if (!ptr || !global_arena)
        return FALSE;

    t_bins_type type = global_arena->tail->bin_type;
    void *heap_start =  global_arena;
    void *heap_end = global_arena->tail + GET_BIN_SIZE(type);

    if (ptr >= heap_start && ptr <= heap_end)
    {
        ft_printf("ptr %p is in the heap\n", ptr);
        return TRUE;
    }

    return FALSE;
}

t_bool is_magic_number_valid(t_bin *bin)
{
    unsigned int expectedMagicNumber = generateMagicNumber(bin->parent_arena);
    ft_printf("bin->size = %zu\n", bin->size);
    char *isfree_str = (bin->is_free == TRUE) ? "TRUE" : "FALSE";
    ft_printf("bin->is_free = %s\n", isfree_str);
    ft_printf("bin->magic_number = %u\n", bin->magic_number);
    ft_printf("expectedMagicNumber = %u\n", expectedMagicNumber);
    // ASSERT(bin->magic_number == expectedMagicNumber);
    if (bin->magic_number != expectedMagicNumber) {
        return FALSE;
    }
    bin->magic_number = 0x1337;
    return TRUE;
}


// Function to coalesce adjacent free bins (noun : coalescence)
t_bin *coalesce_adjacent_free_bins(t_bin* curr_free_bin) {
    t_arena* arena = (t_arena*)((char*)curr_free_bin->parent_arena);
    t_bin* next_bin = curr_free_bin->next;
    t_bin* prev_bin = curr_free_bin->prev;
    t_bin*  merged_bin = curr_free_bin;

    if (next_bin && next_bin->is_free) {
        // Coalesce with next bin
        curr_free_bin->size += BIN_HEADER_SIZE + next_bin->size;
        curr_free_bin->next = next_bin->next;
        if (next_bin->next)
            next_bin->next->prev = curr_free_bin;
    }

    if (prev_bin && prev_bin->is_free) {
        // Coalesce with previous bin
        prev_bin->size += BIN_HEADER_SIZE + curr_free_bin->size;
        prev_bin->next = curr_free_bin->next;
        if (curr_free_bin->next)
            curr_free_bin->next->prev = prev_bin;

        merged_bin = prev_bin;
    }

    return merged_bin;
}

void free_arena(t_bin* bin)
{
   t_arena* arena = bin->parent_arena;

    ft_printf("----- BEFOR ARENA TO REMOVE INFOS -----\n");
    print_arenas();

    if (global_arena == arena) {
        if (arena->next) {
            arena->next->tail = global_arena->tail;
            global_arena = arena->next;
        }
        else {
            global_arena = NULL;
        }
    } else if (global_arena->tail == arena) {
        global_arena->tail = arena->prev;
    }
    if (arena->prev) {
        arena->prev->next = arena->next;
    }
    if (arena->next) {
        arena->next->prev = arena->prev;
    }
    // if (global_arena == NULL) {
    //     global_arena->tail = NULL;
    // }

    ft_printf("----- ARENAs INFOS -----\n");
    print_arenas();
    // exit(0);

    int ret = munmap((void *)arena, arena->mapped_size);
    ft_printf("\nARENA REMOVED\n");
    if (ret == -1) {
      ft_printf("munmap failed\n");
      return;
    }

     // Update tail pointer
    // if (global_arena && global_arena->tail == arena) {
    //     global_arena->tail = global_arena->prev;
    // }

    // arena->prev = NULL;
    // arena->next = NULL;
}

// t_bool free_large_bin(void* bin) {

//     // void *mmapped_ptr = (void*)((char*)bin - ARENA_HEADER_SIZE);
//     t_arena* arena = (t_arena*)(((t_bin*)bin)->parent_arena);
//     ft_printf("\nlarge bin PARENT ARENA = %p\n", arena);
//     // ft_printf("\nremove LARGE mmapped_ptr = %p\n", mmapped_ptr);

//     // handle pointers next/prev arena
//     if (arena->prev) {
//         arena->prev->next = arena->next;
//     }
//     if (arena->next) {
//         arena->next->prev = arena->prev;
//     }

//     int ret = munmap((void *)arena, arena->mapped_size);

//     if (ret == -1) {
//         ft_printf("munmap failed\n");
//         return FALSE;
//     }

//     return TRUE;
// }

t_bool free_tiny_small_bin(void* bin) {
    ((t_bin *)bin)->is_free = TRUE;

    // handle free_size
    t_arena* arena = (t_arena*)(((t_bin*)bin)->parent_arena);
    ft_printf("/////parent_arena = %p\n", arena);

    arena->free_size += ((t_bin*)bin)->size; // pre-existing bin, means it has already a BIN_HEADER_SIZE, we still need it for future allocations

    return TRUE;
}

void my_free(void* ptr) {

t_bin* bin = (t_bin*)((char*)ptr - sizeof(t_bin));

ft_printf("ret_ptr = %p\n", ptr);
ft_printf("bin_ptr = %p\n", bin);

if (!is_within_the_heap(bin) || !is_magic_number_valid(bin))
{
    ft_printf("***************INVALID PTR *********\n");
     return;
}

t_bins_type bin_type = get_bins_type(bin->size);
char *bin_type_str = (bin_type == TINY) ? "TINY" : (bin_type == SMALL) ? "SMALL" : "LARGE";
ft_printf("bin_type = %s\n", bin_type_str);

if (bin_type == LARGE) {
    bin->is_free = TRUE;
    free_arena(bin);
    return;
}

free_tiny_small_bin(bin);

t_bin *merged_bin = coalesce_adjacent_free_bins(bin);

//    print_bin(bin);
//                 exit(0);

if (merged_bin && merged_bin->next == NULL) {
    // Update the tail bin in the arena
    set_last_bin_in_arena(merged_bin);
}

ft_printf("merged_bin = %p\n", merged_bin);
ft_printf("lastBin = %p\n", merged_bin->parent_arena->last_tiny_bin);
ft_printf("global->lastBin = %p\n", global_arena->last_tiny_bin);

if (merged_bin && !merged_bin->next && !merged_bin->prev) {
    // If the bin is the last bin in the arena, check if the arena is empty
    ft_printf("\n\nArena is empty\n\n");
    free_arena(merged_bin);
    return;
}

ft_printf("\nafter Merge\n");
t_arena* arena = (t_arena*)((char*)merged_bin->parent_arena);
// ft_printf("total_bins_count = %zu\n", arena->allocated_bins_count);
ft_printf("mapped_size = %zu\n", arena->mapped_size);
ft_printf("free_size = %zu\n", arena->free_size);
ft_printf("mapped_size - free_size = %zu\n", arena->mapped_size - arena->free_size);
}

