# include "../inc/malloc.h"
#include <stdio.h>

// Function to split a bin if it is large enough
void split_bin(t_bin* bin, size_t size)  // refer to Marwan Burelle's pdf p 10
{    
    t_bin* new_free_bin = (t_bin*)((void*)bin + BIN_HEADER_SIZE + size);
    new_free_bin->size = bin->size - (size - BIN_HEADER_SIZE);
    new_free_bin->next = bin->next;
    new_free_bin->prev = bin;
    new_free_bin->is_free = TRUE;

    bin->size = size;
    bin->next = new_free_bin;
    bin->is_free = FALSE;
}

// t_bin* find_best_fit(t_bins_type binType, size_t size, t_arena** arenaa)
// {
//     t_arena* arena = global_arena;
//     while (arena) {
//         if (arena->bin_type == binType && !arena->is_full) {
//             t_bin* curr_bin = (t_bin*)((char*)arena + ARENA_HEADER_SIZE);
//             t_bin* best_fit = NULL;
//             size_t best_fit_size = -1;

//             while (curr_bin) {
//                 if (curr_bin->is_free && curr_bin->size >= size) {
//                     if (curr_bin->size == size)
//                     {
//                         *arenaa = arena;
//                         return curr_bin;
//                     }
//                     else if (curr_bin->size < best_fit_size) {
//                         best_fit = curr_bin;
//                         best_fit_size = curr_bin->size;
//                     }
//                 }
//                 curr_bin = curr_bin->next;
//             }
//             // arenaa = &arena;
//             *arenaa = arena;
//             return best_fit;
//         }
//         arena = arena->next;
//     }

//     *arenaa = NULL;
//     return NULL;
// }

t_arena* find_best_fit_arena(t_bins_type binType, size_t size)
{
    t_arena* curr_arena = global_arena;
    t_arena* best_fit_arena = NULL;

     if (curr_arena == NULL) {
        return NULL;
    }

    size_t best_fit_size = -1;

    while (curr_arena) {
        if (curr_arena->bin_type == binType && curr_arena->free_size >= size && !curr_arena->free_size) {
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
    if (arena == NULL) {
        return NULL;
    }

    t_bin* curr_bin = (t_bin*)((void*)arena + ARENA_HEADER_SIZE);
    t_bin* best_fit_bin = NULL;
    t_bin *last_bin = NULL;
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
        last_bin = curr_bin;
        curr_bin = curr_bin->next;
    }

    return best_fit_bin;// ? best_fit_bin : last_bin;
}

t_bin *get_last_bin(t_arena *arena, t_bins_type binType) {
    return (binType == TINY) ? (t_bin *)((void *)arena->last_tiny_bin) : (t_bin *)((void *)arena->last_small_bin);
}

void set_last_bin(t_arena **best_fit_arena , t_bins_type binType, t_bin *bin) {
    if (binType == TINY) {
        (*best_fit_arena)->last_tiny_bin = bin;
    } else if (binType == SMALL) {
        (*best_fit_arena)->last_small_bin = bin;
    }
}

t_bin *append_new_bin(t_arena *best_fit_arena , t_bins_type binType, size_t size) {
    t_bin *last_prev_bin = get_last_bin(best_fit_arena, binType);
    t_bin *new_bin;
    ASSERT(last_prev_bin != NULL);
    
    new_bin = (t_bin *)((void *)last_prev_bin + BIN_HEADER_SIZE + last_prev_bin->size);
    last_prev_bin->next = new_bin;
  

    new_bin->size = size;
    new_bin->next = NULL;
    new_bin->prev = last_prev_bin;
    new_bin->is_free = FALSE;
    set_last_bin(&best_fit_arena, binType, new_bin);

    return new_bin;
}

t_bin *find_best_fit(t_bins_type binType, size_t size) {
    t_arena *best_fit_arena = find_best_fit_arena(binType, size);
    t_bin *best_fit_bin = find_best_fit_bin(best_fit_arena, size);

    if (best_fit_bin) {
        ASSERT(best_fit_bin->is_free == TRUE);
        ASSERT(best_fit_bin->size >= size);
        ASSERT(best_fit_bin->size >= size + BIN_HEADER_SIZE);
        // Split the bin if it is large enough
        if (best_fit_bin->size >= size + BIN_HEADER_SIZE) {
            ASSERT(best_fit_bin->size >= size + BIN_HEADER_SIZE);
            split_bin(best_fit_bin, size);
        } else {
            best_fit_bin->is_free = FALSE;
            best_fit_bin->size = size;
        }

        best_fit_arena->free_size -= size + BIN_HEADER_SIZE; //*********
        best_fit_arena->allocated_bins_count++;

        return best_fit_bin;
    } else if (best_fit_arena && !best_fit_bin) {
        t_bin *new_bin = append_new_bin(best_fit_arena, binType, size);

        best_fit_arena->free_size -= size + BIN_HEADER_SIZE;
        best_fit_arena->allocated_bins_count++;
        return new_bin;
    }

    return NULL;
}