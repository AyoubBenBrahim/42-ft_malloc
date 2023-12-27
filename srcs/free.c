
#include "../inc/malloc.h"
#include <stdlib.h>
#include <sys/mman.h>

t_bool is_valid_ptr(void *ptr)
{
    if (!ptr || !global_arena)
        return FALSE;
  

    t_bins_type type = global_arena->last->bin_type;
    void *heap_start =  global_arena;
    void *heap_end = global_arena->last + GET_BIN_SIZE(type);

    ft_printf("heap_start = %p\n", heap_start);
    ft_printf("heap_end = %p\n", heap_end);

    void *ptr1 = heap_start - 100;
    void *ptr2 = heap_end + 100;

    void *ptr3 = heap_start + 100;
    void *ptr4 = heap_end + 1;

    // #check if the pointer is in the heap
    if (ptr1 >= heap_start && ptr1 <= heap_end)
    {
        ft_printf("ptr1 %p is in the heap\n", ptr1);
        // return TRUE;
    }
    else
    {
        ft_printf("ptr1 %p is not in the heap\n", ptr1);
        // return FALSE;
    }
    if (ptr2 >= heap_start && ptr2 <= heap_end)
    {
        ft_printf("ptr2 %p is in the heap\n", ptr2);
        // return TRUE;
    }
    else
    {
        ft_printf("ptr2 %p is not in the heap\n", ptr2);
        // return FALSE;
    }
/*************************/
    if (ptr3 >= heap_start && ptr3 <= heap_end)
    {
        ft_printf("ptr3 %p is in the heap\n", ptr3);
        // return TRUE;
    }
    else
    {
        ft_printf("ptr3 %p is not in the heap\n", ptr3);
        // return FALSE;
    }
    if (ptr4 >= heap_start && ptr4 <= heap_end)
    {
        ft_printf("ptr4 %p is in the heap\n", ptr4);
        // return TRUE;
    }
    else
    {
        ft_printf("ptr4 %p is not in the heap\n", ptr4);
        // return FALSE;
    }

    return FALSE;
}

t_bool is_valid_bin(t_bin *bin)
{
    
    // Check the magic number
    unsigned int expectedMagicNumber = generateMagicNumber();
    ft_printf("bin->size = %zu\n", bin->size);
    char *isfree_str = (bin->is_free == TRUE) ? "TRUE" : "FALSE";
    ft_printf("bin->is_free = %s\n", isfree_str);
    ft_printf("bin->magic_number = %u\n", bin->magic_number);
    ft_printf("expectedMagicNumber = %u\n", expectedMagicNumber);
    ASSERT(bin->magic_number == expectedMagicNumber);
    if (bin->magic_number != expectedMagicNumber) {
        // Handle invalid bin case
        return FALSE;
    }
    return TRUE;
}


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

t_bool free_large_bin(void* bin) {

    void *mmapped_ptr = (void*)((char*)bin - sizeof(t_arena));
    ft_printf("remove mmapped_ptr = %p\n", mmapped_ptr);
    // ((t_bin *)bin)->is_free = TRUE;
    // return TRUE;

    // handle pointers next/prev arena
    if (((t_arena*)mmapped_ptr)->prev) {
        ((t_arena*)mmapped_ptr)->prev->next = ((t_arena*)mmapped_ptr)->next;
    }
    if (((t_arena*)mmapped_ptr)->next) {
        ((t_arena*)mmapped_ptr)->next->prev = ((t_arena*)mmapped_ptr)->prev;
    }

    int ret = munmap(mmapped_ptr, ((t_arena*)mmapped_ptr)->allocated_size);

    if (ret == -1) {
        ft_printf("munmap failed\n");
        return FALSE;
    }

    return TRUE;
}

void my_free(void* ptr) {
  
// if (!is_valid_ptr(ptr))
//     return;

t_bin* bin = (t_bin*)((char*)ptr - sizeof(t_bin));

ft_printf("ret_ptr = %p\n", ptr);
ft_printf("bin_ptr = %p\n", bin);

if (!is_valid_bin(bin))
    return;

t_bins_type bin_type = get_bins_type(bin->size);
char *bin_type_str = (bin_type == TINY) ? "TINY" : (bin_type == SMALL) ? "SMALL" : "LARGE";
ft_printf("bin_type = %s\n", bin_type_str);

if (bin_type == LARGE) {
    free_large_bin(bin);
    return;
}


//   bin->is_free = TRUE;

//   // Coalesce adjacent free bins
//   t_arena* arena = (t_arena*)((char*)bin - sizeof(t_arena));
//   coalesce_bins(arena, (t_bin*)((char*)arena + sizeof(t_arena)));

//     // If the bin is the last bin in the arena, check if the arena is empty
//     if_last_bin_free_arena(bin);
}

// t_block fusion(t_block b){
//  if (b->next && b->next->free){
//  b->size += BLOCK_SIZE + b->next->size;
//  b->next = b->next->next;
//  if (b->next)
//  b->next->prev = b;
//  }
//  return (b);
//  }