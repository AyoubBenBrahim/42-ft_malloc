
#include "../inc/malloc.h"

pthread_mutex_t mallocMutex = PTHREAD_MUTEX_INITIALIZER;



void show_alloc_mem()
{
    pthread_mutex_lock(&mallocMutex);
    show_alloc();
    pthread_mutex_unlock(&mallocMutex);
}

void* safe_malloc(size_t size) {
    pthread_mutex_lock(&mallocMutex);
    void* ptr = my_malloc(size);
    pthread_mutex_unlock(&mallocMutex);
    return ptr;
}

void safe_free(void* ptr) {
    pthread_mutex_lock(&mallocMutex);
    my_free(ptr);
    pthread_mutex_unlock(&mallocMutex);
}

void    *safe_realloc(void* ptr, size_t size) {
    pthread_mutex_lock(&mallocMutex);
    void* newPtr = my_realloc(ptr, size);
    pthread_mutex_unlock(&mallocMutex);
    return newPtr;
}

void    *safe_calloc(size_t count, size_t size) {
    pthread_mutex_lock(&mallocMutex);
    void* ptr = my_calloc(count, size);
    pthread_mutex_unlock(&mallocMutex);
    return ptr;
}

void    *malloc(size_t size) {
    ft_printf("start malloc\n");
    return safe_malloc(size);
}

void free(void* ptr) {
    safe_free(ptr);
}

void    *calloc(size_t count, size_t size) {
    return safe_calloc(count, size);
}

void* realloc(void* ptr, size_t size) {
    return safe_realloc(ptr, size);
}
