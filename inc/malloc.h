#ifndef _MALLOC_H
#define _MALLOC_H

#include "../libft/libft.h"
#include <sys/types.h>
# include <unistd.h>
# include <sys/mman.h>
# include <sys/resource.h>
# include <stdint.h>
# include <stddef.h>
# include <string.h>
# include <stdlib.h>
#include <sys/_types/_uintptr_t.h>
#include <pthread.h>

# include <assert.h>
# define ASSERT assert

// pthread_mutex_t mallocMutex = PTHREAD_MUTEX_INITIALIZER;

# define PAGE_SIZE		4096

# define BIN_CAPACITY 128

# define TINY_BINS_ARENA_PAGE (4 * PAGE_SIZE) // 16KB
# define TINY_BIN_SIZE (TINY_BINS_ARENA_PAGE / BIN_CAPACITY) // 128

# define SMALL_BINS_ARENA_PAGE (16 * PAGE_SIZE) // 65K 65536
# define SMALL_BIN_SIZE (SMALL_BINS_ARENA_PAGE / BIN_CAPACITY) // 512

#define IS_TINY(x) (x <= TINY_BIN_SIZE)
#define IS_SMALL(x) (x > TINY_BIN_SIZE && x <= SMALL_BIN_SIZE)
#define IS_LARGE(x) (x > SMALL_BIN_SIZE)

# define ARENA_HEADER_SIZE sizeof(t_arena)
# define BIN_HEADER_SIZE sizeof(t_bin)

#define METADATA_SIZE(REQUESTED_SIZE) (ARENA_HEADER_SIZE + BIN_HEADER_SIZE + REQUESTED_SIZE)

#define ROUND_TO_MULTIPLE_OF_16(x) (((x) + 15) & ~0xF)

#define ALIGN4(x) (((( (x) - 1) >> 2) << 2 ) + 4 )

#define ALIGN8(x) (((( (x) - 1) >> 3) << 3) + 8 )

# define  GET_BIN_SIZE(type) (type == TINY ? TINY_BINS_ARENA_PAGE : SMALL_BINS_ARENA_PAGE)

typedef enum        e_bool
{
    FALSE,
    TRUE
}                   t_bool;

typedef enum e_bins_type {
    TINY,
    SMALL,
    LARGE
} t_bins_type;

typedef struct s_bin {
    size_t          size;
    struct s_bin	*prev;
	struct s_bin	*next;
    t_bool          is_free;
    unsigned int    magic_number;
    struct s_arena  *parent_arena;
}				t_bin;



typedef struct	s_arena {
	struct s_arena	*next;
    struct s_arena	*prev;
    struct s_arena  *tail;
    struct s_bin	*last_tiny_bin;
    struct s_bin	*last_small_bin;
    t_bins_type     bin_type;
    size_t			mapped_size;
	size_t			free_size;
	size_t			allocated_bins_count;
}				t_arena;

t_arena         *global_arena;

void            *ft_malloc(size_t size);
void            ft_free(void* ptr);
void            *safe_malloc(size_t size);
void            safe_free(void* ptr);
void            *my_malloc(size_t size);
void            my_free(void* ptr);

t_bool          check_sys_limit(size_t size);
void*           request_new_page_mmap(t_bins_type bins_type, size_t mapped_size);
t_bin*          find_best_fit(t_bins_type binType, size_t size);
t_bin*          find_best_fit_bin(t_arena* arena, size_t size);
t_arena*        find_best_fit_arena(t_bins_type binType, size_t size);
void            split_bin(t_bin* bin, size_t size);
void            *handle_large_bins(t_bins_type bins_type, size_t size);

t_bins_type     get_bins_type(size_t size);

void            *my_malloc(size_t size);
t_bins_type     get_bins_type(size_t size);

void            print_arena(t_arena *arena);
void            print_arenas();
void            print_bins();

t_bin           *get_last_bin_in_arena(t_arena *arena, t_bins_type binType);
void            set_last_bin_in_arena( t_bin *bin);

t_bin           *append_new_bin(t_arena *arena, t_bins_type binType, size_t size);

t_bin           *create_new_arena(t_bins_type bins_type, size_t size);

t_bool          is_within_the_heap(void *ptr);

unsigned int    generateMagicNumber(t_arena *parent_arena);
t_bool         is_magic_number_valid(t_bin *bin);


t_bool          free_large_bin(void* bin);
t_bool          free_tiny_small_bin(void* bin);
t_bin           *coalesce_adjacent_free_bins(t_bin* curr_free_bin);

#endif