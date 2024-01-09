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