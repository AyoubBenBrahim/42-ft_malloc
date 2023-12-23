
#include "../inc/malloc.h"
/*

// Function to coalesce adjacent free blocks
void coalesce_blocks(block_t* block) {
    if (block->next && block->next->free) {
        block->size += BLOCK_SIZE + block->next->size;
        block->next = block->next->next;
    }
}

// Function to consolidate free blocks
void malloc_consolidate() {
    block_t* current = free_list;
    while (current && current->next) {
        if (current->free && current->next->free) {
            current->size += BLOCK_SIZE + current->next->size;
            current->next = current->next->next;
        } else {
            current = current->next;
        }
    }
}

// Function to free memory
void free(void* ptr) {
    if (!ptr)
        return;

    // Get the block metadata
    block_t* block = (block_t*)((char*)ptr - BLOCK_SIZE);

    // Mark the block as free
    block->free = 1;

    // Coalesce adjacent free blocks
    coalesce_blocks(block);

    // Consolidate free blocks
    malloc_consolidate();
}
*/

void coalesce_bins(t_arena* arena, t_bin* start_bin) {
//   t_bin* current_bin = start_bin;

//   while (current_bin->next && current_bin->next->is_free && current_bin->next->bin_type == current_bin->bin_type) {
//     // Coalesce adjacent free bins
//     t_bin* next_bin = current_bin->next;
//     current_bin->size += next_bin->size + sizeof(t_bin);
//     current_bin->next = next_bin->next;
//   }
}

void if_last_bin_free_arena(t_bin* bin)
{
//  if (bin->next == NULL) {
//     // If the bin is the last bin in the arena, check if the arena is empty
//     t_bin* current_bin = (t_bin*)((char*)arena + sizeof(t_arena));
//     while (current_bin) {
//       if (!current_bin->is_free) {
//         return; // Arena is not empty
//       }
//       current_bin = current_bin->next;
//     }

//     // Arena is empty, free it
//     if (arena->prev) {
//       arena->prev->next = arena->next;
//     }
//     if (arena->next) {
//       arena->next->prev = arena->prev;
//     }
//     if (arena == global_arena) {
//       global_arena = arena->next;
//     }
//     munmap(arena, arena->size);
//   }
}

void my_free(void* ptr) {
  if (!ptr) {
    return; // Ignore NULL pointers
  }

  t_bin* bin = (t_bin*)((char*)ptr - sizeof(t_bin));
  bin->is_free = TRUE;

  // Coalesce adjacent free bins
  t_arena* arena = (t_arena*)((char*)bin - sizeof(t_arena));
  coalesce_bins(arena, (t_bin*)((char*)arena + sizeof(t_arena)));

    // If the bin is the last bin in the arena, check if the arena is empty
    if_last_bin_free_arena(bin);
}