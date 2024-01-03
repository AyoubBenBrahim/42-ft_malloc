# include "../inc/malloc.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

t_bool is_out_of_arena_boundary(t_arena* arena, size_t size)
{
    // t_arena* arena = bin->parent_arena;
    t_bin *last_prev = get_last_bin_in_arena(arena, arena->bin_type);
    ASSERT(last_prev != NULL);
    void* arena_start = (void*)arena;
    void* arena_end = (void*)arena + arena->mapped_size;
    void* new_bin = (void*)last_prev + BIN_HEADER_SIZE + last_prev->size;

    // if (arena->next)
    //     arena_end = arena->next;

    if ((void*)new_bin > arena_end || (void*)new_bin + BIN_HEADER_SIZE + size > arena_end)
    {
        ft_printf("size = %zu\n", size);
        ft_printf("arena_start = %p\n", arena_start);
        // exit(0);
        return TRUE;
    }
    return FALSE;
}

// Function to split a bin if it is large enough
t_bool split_bin(t_bin* best_fit_bin, size_t size)  // refer to Marwan Burelle's pdf p 10
{    
    t_bin* new_free_bin = (t_bin*)((void*)best_fit_bin + BIN_HEADER_SIZE + size);// bin [      size|        bin_size]     

    new_free_bin->size = best_fit_bin->size - size - BIN_HEADER_SIZE;           
    new_free_bin->next = best_fit_bin->next;
    new_free_bin->prev = best_fit_bin;
    new_free_bin->is_free = TRUE;
    new_free_bin->parent_arena = best_fit_bin->parent_arena;

    best_fit_bin->size = size;
    best_fit_bin->next = new_free_bin;
    best_fit_bin->is_free = FALSE;

    if (new_free_bin->next)
        new_free_bin->next->prev = new_free_bin;

    if (new_free_bin->next == NULL)
        set_last_bin_in_arena(new_free_bin);

    new_free_bin->magic_number = 1337;

    best_fit_bin->parent_arena->free_size -= BIN_HEADER_SIZE;
ASSERT(size != 104); 
    return  TRUE;
}

t_arena* find_best_fit_arena(t_bins_type binType, size_t size)
{
    t_arena* curr_arena = global_arena;
    t_arena* best_fit_arena = NULL;

     if (curr_arena == NULL)
        return NULL;

    size_t best_fit_size = -1;

    while (curr_arena) {
        if (curr_arena->bin_type == binType && curr_arena->free_size >= size && !is_out_of_arena_boundary(curr_arena, size)) {
            if (curr_arena->free_size == size) {
                return curr_arena;
            }
            else if (curr_arena->free_size < best_fit_size) {
                best_fit_arena = curr_arena;
                best_fit_size = curr_arena->free_size;
            }
        }
        curr_arena = curr_arena->next;
    }

    return best_fit_arena;
}

t_bin* find_best_fit_bin(t_arena* arena, size_t size)
{ 
    t_bin* curr_bin = (t_bin*)((void*)arena + ARENA_HEADER_SIZE);
    t_bin* best_fit_bin = NULL;
    size_t best_fit_size = -1;

    while (curr_bin) {
        if (curr_bin->is_free && curr_bin->size >= size) {
            if (curr_bin->size == size) {
                return curr_bin;
            }
            else if (curr_bin->size < best_fit_size) {
                best_fit_bin = curr_bin;
                best_fit_size = curr_bin->size;
            }
        }
        curr_bin = curr_bin->next;
    }

    return best_fit_bin;
}

t_bin *get_last_bin_in_arena(t_arena *arena, t_bins_type binType) {
    return (binType == TINY) ? 
    (t_bin *)((void *)arena->last_tiny_bin) : (t_bin *)((void *)arena->last_small_bin);
}

void set_last_bin_in_arena(t_bin *bin) {
    t_arena *arena = bin->parent_arena;
    t_bins_type binType = arena->bin_type;
    if (binType == TINY) {
        arena->last_tiny_bin = bin;
    } else if (binType == SMALL) {
        arena->last_small_bin = bin;
    }
}

/*
handle this case where free_size == TINY_BIN_MAX or SMALL_BIN_MAX

char *ptr1 = (char *)my_malloc(TINY_BIN_MAX);
    for (int i = 1; i <= 100; i++)
    {
        my_malloc(TINY_BIN_MAX);
    }

    char *ptr40 = (char *)my_malloc(64);
     my_free(ptr40);
    char *ptr7 = (char *)my_malloc(80);
*/

// void append_free_bin(t_arena *arena, t_bins_type binType, size_t size) {
//     t_bin *last_prev_bin = get_last_bin_in_arena(arena, binType);
//     t_bin *new_bin;
//     ASSERT(last_prev_bin != NULL);
    
//     if (is_out_of_arena_boundary(arena, size))
//     {
//         ft_printf("** append is_out_of_arena_boundary** \n");
//         return;
//     }
//     new_bin = (t_bin *)((void *)last_prev_bin + BIN_HEADER_SIZE + last_prev_bin->size);
//     last_prev_bin->next = new_bin;

//     new_bin->size = size;
//     new_bin->next = NULL;
//     new_bin->prev = last_prev_bin;
//     new_bin->is_free = TRUE;
//     new_bin->parent_arena = arena;
//     new_bin->magic_number = generateMagicNumber(new_bin->parent_arena);
//     set_last_bin_in_arena(new_bin);
//     arena->free_size -= size + BIN_HEADER_SIZE;

//     // return new_bin;
// }

t_bin *append_new_bin(t_arena *best_fit_arena , t_bins_type binType, size_t size) {
    t_bin *last_prev_bin = get_last_bin_in_arena(best_fit_arena, binType);
    t_bin *new_bin;
    ASSERT(last_prev_bin != NULL);
    
    new_bin = (t_bin *)((void *)last_prev_bin + BIN_HEADER_SIZE + last_prev_bin->size);
    last_prev_bin->next = new_bin;

    new_bin->size = size;
    new_bin->next = NULL;
    new_bin->prev = last_prev_bin;
    new_bin->is_free = FALSE;
    new_bin->parent_arena = best_fit_arena;
    new_bin->magic_number = generateMagicNumber(new_bin->parent_arena);
    set_last_bin_in_arena(new_bin);
    best_fit_arena->free_size -= size + BIN_HEADER_SIZE;

    

    // if (best_fit_arena->free_size == TINY_BIN_MAX || best_fit_arena->free_size == SMALL_BIN_MAX)
    // {


    // }


    return new_bin;
}

t_bin *find_best_fit(t_bins_type binType, size_t size) {
    t_arena *best_fit_arena = find_best_fit_arena(binType, size);

    if (!best_fit_arena)
        return NULL;

    t_bin *best_fit_bin = find_best_fit_bin(best_fit_arena, size);

    if (best_fit_bin) {
        ASSERT(best_fit_bin->is_free == TRUE);
        ASSERT(best_fit_bin->size >= size);
        t_bool split = FALSE;
        // Split the bin if it is large enough
        if (best_fit_bin->size > size + BIN_HEADER_SIZE) {
            ASSERT(best_fit_bin->size > size + BIN_HEADER_SIZE);
            split = split_bin(best_fit_bin, size);
        }
        if (split == FALSE)
        {
            best_fit_bin->is_free = FALSE;
            best_fit_bin->size = size;            
        }


        best_fit_bin->magic_number =
            generateMagicNumber(best_fit_bin->parent_arena);

        // best_fit_arena->free_size -= size + BIN_HEADER_SIZE;
        // we only need to update the free_size when we create a new arena
        // or when we free a bin or when we append a new bin

        return best_fit_bin;
    }
    if (best_fit_arena && best_fit_arena->free_size >= size + BIN_HEADER_SIZE) {
        ASSERT(best_fit_bin == NULL);
        ASSERT(best_fit_arena != NULL);
        ASSERT(best_fit_arena->free_size >= size + BIN_HEADER_SIZE);
        // t_bin *new_bin = get_last_bin_in_arena(best_fit_arena, binType);
        // ASSERT(new_bin != NULL);
        // new_bin->parent_arena = best_fit_arena;
        // if (is_out_of_arena_boundary(new_bin, size))
        // {
        //     ft_printf("** append is_out_of_arena_boundary** \n");
        //     return FALSE;
        // }
        t_bin *new_bin = append_new_bin(best_fit_arena, binType, size);
    
        return new_bin;
    }

    return NULL;
}