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

/*
**
** b is a multiple of a if b = na
** The size of these zones must be a multiple of getpagesize().
** means that the size of the zone must be a multiple of 4096
** as b = na, zone_size = n * getpagesize() 
** zone_size % getpagesize() == 0
** 
** check script in /srcs/helpers/zone_size.c
** 
** TINY_BINS
** 
** "(4096*4)/(136)" = 120
** 
** "(4096*4)/(120+40)" = 102
** 
** "(4*4096) - ((120 + 40) * 100 + 64)" = 320
** "(4096*4) - ((120+40) * 102 + 64)" = 0
** 
** arena->free_size = 320 (we can fit 2 bins 160+160)
** 
** 
** SMALL_BINS
** 
**  "(4096*26)/104" = 1024
**  "(4096*26)/(1024+40)" = 100
**  "(4096*26) - ((1024+40) * 100 + 64)" = 32
** 
** "(4096*26) - (((4096*26)/(104)+40) * 100 + 64)" = 32 nzr3o fiha limoun
** 
*/


# define PAGE_SIZE		4096
# define T_BIN_CAPACITY   136 // size = 120
# define S_BIN_CAPACITY   104 // size = 1024

# define TINY_BINS_ARENA_PAGE (4 * PAGE_SIZE) // 12K 12288
# define TINY_BIN_MAX (TINY_BINS_ARENA_PAGE / T_BIN_CAPACITY) 

# define SMALL_BINS_ARENA_PAGE (26 * PAGE_SIZE) // 104K 106496
# define SMALL_BIN_MAX (SMALL_BINS_ARENA_PAGE / S_BIN_CAPACITY) // 

#define IS_TINY(x) (x <= TINY_BIN_MAX)
#define IS_SMALL(x) (x > TINY_BIN_MAX && x <= SMALL_BIN_MAX)
#define IS_LARGE(x) (x > SMALL_BIN_MAX)

/*
* sizeof(t_arena) = 64 = 0x40
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
}				t_arena;

t_arena         *global_arena;

void            *ft_malloc(size_t size);
void            *safe_malloc(size_t size);
void            *my_malloc(size_t size);

void            ft_free(void* ptr);
void            safe_free(void* ptr);
void            my_free(void* ptr);

void            *ft_calloc(size_t count, size_t size);
void            *safe_calloc(size_t count, size_t size);
void            *my_calloc(size_t count, size_t size);

void            *ft_realloc(void *ptr, size_t size);
void            *safe_realloc(void *ptr, size_t size);
void            *my_realloc(void *ptr, size_t size);

t_bool          check_sys_limit(size_t size);
void*           request_new_page_mmap(t_bins_type bins_type, size_t mapped_size);
t_bin*          find_best_fit(t_bins_type binType, size_t size);
t_bin*          find_best_fit_bin(t_arena* arena, size_t size);
t_arena*        find_best_fit_arena(t_bins_type binType, size_t size);
t_bool          split_bin(t_bin* bin, size_t size);

t_bins_type     get_bins_type(size_t size);

t_bins_type     get_bins_type(size_t size);

void            print_arena(t_arena *arena);
void            print_arenas();
void            print_bin(t_bin *bin);
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


t_bool is_out_of_arena_boundary(t_arena* arena, size_t size);
#endif