
#include "../inc/malloc.h"

pthread_mutex_t mallocMutex = PTHREAD_MUTEX_INITIALIZER;

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

void    *ft_malloc(size_t size) {
    return safe_malloc(size);
}

void ft_free(void* ptr) {
    safe_free(ptr);
}

void    *ft_calloc(size_t count, size_t size) {
    return safe_calloc(count, size);
}

void* ft_realloc(void* ptr, size_t size) {
    return safe_realloc(ptr, size);
}
