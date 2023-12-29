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


// b is a multiple of a if b = na
// The size of these zones must be a multiple of getpagesize().
// means that the size of the zone must be a multiple of 4096
// as b = na, zone_size = n * getpagesize() 
// zone_size % getpagesize() == 0

/*

"(3*4096) - ((82 + 40) * 100 + 72)" = 16
*************

"(4*4096) - ((123 + 40) * 100 + 72)" = 12


"(16*4096) - ((614 + 40) * 100 + 72)" = 64

*/



# define PAGE_SIZE		4096
# define T_BIN_CAPACITY   128// (3*4096) / (82+40) = 100.7
# define S_BIN_CAPACITY   128 // (16*4096) / (614+40) = 100.2
# define CAPACITY 136

# define TINY_BINS_ARENA_PAGE (4 * PAGE_SIZE) // 12K 12288
# define TINY_BIN_SIZE (TINY_BINS_ARENA_PAGE / CAPACITY) 

# define SMALL_BINS_ARENA_PAGE (16 * PAGE_SIZE) // 65K 65536
# define SMALL_BIN_SIZE ALIGN8(SMALL_BINS_ARENA_PAGE / CAPACITY) // 512

#define IS_TINY(x) (x <= TINY_BIN_SIZE)
#define IS_SMALL(x) (x > TINY_BIN_SIZE && x <= SMALL_BIN_SIZE)
#define IS_LARGE(x) (x > SMALL_BIN_SIZE)

/*
* sizeof(t_arena) = 72 = 0x48
* sizeof(t_bin) = 40 = 0x28
*/

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
	// size_t			allocated_bins_count;
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

t_bins_type     get_bins_type(size_t size);

void            *my_malloc(size_t size);
t_bins_type     get_bins_type(size_t size);

void            print_arena(t_arena *arena);
void            print_arenas();
void            print_bins();
void            print_headers_info(int requested_size);

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