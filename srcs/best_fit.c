# include "../inc/malloc.h"

// Function to split a bin if it is large enough
void split_bin(t_bin* bin, size_t size) { // refer to Marwan Burelle's pdf p 10
    t_bin* new_free_bin = (t_bin*)((char*)bin + sizeof(t_bin) + size);
    new_free_bin->size = bin->size - size - sizeof(t_bin);
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
//             t_bin* curr_bin = (t_bin*)((char*)arena + sizeof(t_arena));
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
        if (curr_arena->bin_type == binType && curr_arena->free_size >= size) {
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

    t_bin* curr_bin = (t_bin*)((char*)arena + sizeof(t_arena));
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

t_bin* find_best_fit(t_bins_type binType, size_t size, t_arena** arenaa)
{
    t_arena* arena = find_best_fit_arena(binType, size);
    t_bin* best_fit_bin = find_best_fit_bin(arena, size);

    *arenaa = arena;
    return best_fit_bin;
}