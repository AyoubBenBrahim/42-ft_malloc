#include "../inc/malloc.h"

/*
** The reallocf() function is identical to the realloc() function, except
** that it will free the passed pointer when the requested memory cannot
** be allocated.  This is a FreeBSD specific API designed to ease the
** problems with traditional coding styles for realloc causing memory
** leaks in libraries.
**
*/

void    *reallocf(void *ptr, size_t size){
    pthread_mutex_lock(&g_mallocMutex);
    void* new_ptr = my_realloc(ptr, size);
    if (!new_ptr)
        my_free(ptr);
    pthread_mutex_unlock(&g_mallocMutex);
    return new_ptr;
}