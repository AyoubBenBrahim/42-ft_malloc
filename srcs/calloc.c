
#include "../inc/malloc.h"

void *my_calloc(size_t count, size_t size)
{
    if (count <= 0 || size <= 0)
        return NULL;

    size_t _size = count * size;
    void *ptr = my_malloc(_size);

    if (!ptr)
        return NULL;

    ft_memset(ptr, 'A', _size);
    return ptr;
}