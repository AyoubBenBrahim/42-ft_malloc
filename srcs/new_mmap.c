
#include "../inc/malloc.h"
#include <stddef.h>
#include <sys/resource.h>


/*
** checking the system limit for the maximum amount of data that can be allocated (RLIMIT_DATA).
** To determine whether the requested size is within the system limit
**
** if you want to check whether the requested size is within the currently set limit, you should use rlim_cur.
** This allows you to consider any specific restrictions or adjustments made to the limit by the system or the user.
*/

t_bool check_sys_limit(size_t size)
{
    struct rlimit limit;

    int ret = getrlimit(RLIMIT_DATA, &limit);
    if (ret == -1)
        return FALSE;

    return (size < limit.rlim_max);
}

// Function to allocate memory using mmap()
void* request_new_page_mmap(t_bins_type bins_type, size_t size) 
{
    void* mem = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (mem == MAP_FAILED || !check_sys_limit(size))
        return NULL;

    
    // block_t* block = (block_t*)mem;
    // block->size = size - BLOCK_SIZE;
    // block->next = NULL;
    // block->free = 0;

    // heap->group = group;
	// heap->total_size = heap_size;
	// heap->free_size = heap_size - sizeof(t_heap);

    // t_arena *new_arena;
    // new_arena->bin_type = bins_type;


    

    // return (void*)((char*)block + BLOCK_SIZE);
    return (t_arena*)mem + METADATA_SIZE(size);
}