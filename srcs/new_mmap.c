#include "../inc/malloc.h"

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

    return (size < limit.rlim_cur);
}

void* request_new_page_mmap(size_t mapped_size)
{
    if (check_sys_limit(mapped_size) == FALSE)
        return NULL;

    void* mem = mmap(NULL, mapped_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (mem == MAP_FAILED || mem == NULL)
        return NULL;

    return (void *)mem;
}

/*
The mmap function is used to map files or devices into memory.
In the given code snippet, the `my_malloc` function is attempting to allocate
a very large amount of memory using mmap with the size of `1000000000000000` bytes.

The failure of mmap could occur due to several reasons:

1. Insufficient available memory: The system may not have enough contiguous memory
 available to fulfill the large memory allocation request.
 mmap requires a contiguous region of memory for the requested size, 
 and if it cannot find a suitable block, it returns MAP_FAILED (-1) to indicate failure.

2. Resource limitations: The operating system may have resource limitations on the maximum size of a single mmap allocation.
 The specific limit can vary depending on the system configuration and settings.

3. Address space exhaustion: If the system's address space is heavily fragmented or nearly exhausted, mmap may fail to find a suitable region to allocate the requested size.

4. Permissions or restrictions: The user running the program may not have the necessary permissions or restrictions set by the operating system to perform the mmap operation.

To determine the exact reason for mmap failure, it would be helpful to check the specific error code or message returned by mmap.
This can be done by examining the value of errno immediately after the mmap call, using the `perror` function or printing the value of `errno` directly.
*/