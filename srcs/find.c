
#include "../inc/malloc.h"

void *find_arena(t_arena* wanted_arena, size_t size) {
    t_arena* current_arena = global_arena;
    while (current_arena) {
        if (current_arena == wanted_arena) {
            return current_arena;
        }
        current_arena = current_arena->next;
    }
    return NULL;
}

void *find_bin(t_bin* wanted_bin) {
    t_arena* current_arena = global_arena;
    while (current_arena) {
        t_bin* current_bin = (t_bin*)((char*)current_arena + sizeof(t_arena));
        while (current_bin) {
            if (current_bin == wanted_bin) {
                return current_bin;
            }
            current_bin = current_bin->next;
        }
        current_arena = current_arena->next;
    }
    return NULL;
}

t_bool is_valid_arena(t_arena* arena) {
    t_arena* current_arena = global_arena;
    while (current_arena) {
        if (current_arena == arena) {
            return TRUE;
        }
        current_arena = current_arena->next;
    }
    return FALSE;
}

t_bool is_valid_bin(t_bin* bin) {
    // t_arena* current_arena = global_arena;
    // while (current_arena) {
    //     t_bin* current_bin = (t_bin*)((char*)current_arena + sizeof(t_arena));
    //     while (current_bin) {
    //         if (current_bin == bin) {
    //             return TRUE;
    //         }
    //         current_bin = current_bin->next;
    //     }
    //     current_arena = current_arena->next;
    // }
    // return FALSE;
    if (bin->valid_ptr == bin) {
        return TRUE;
    }
}