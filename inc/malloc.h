#ifndef _MALLOC_H
#define _MALLOC_H

# include <unistd.h>
# include <stdio.h>
# include <sys/mman.h>
# include <sys/resource.h>
# include <stdint.h>
# include <stddef.h>
# include <string.h>

#include <stdio.h>
#include <stdlib.h>


# include <assert.h>
# define ASSERT assert



#define ROUND_TO_MULTIPLE_OF_16(x) (((x) + 15) & ~15)

# define PAGE_SIZE		4096

# define ZONE_NBR_ELEMENTS 128

# define TINY_BINS_ARENA (4 * PAGE_SIZE)
# define TINY_BIN_SIZE (TINY_BINS_ARENA / ZONE_NBR_ELEMENTS)

# define SMALL_BINS_ARENA (32 * PAGE_SIZE)
# define SMALL_BIN_SIZE (SMALL_BINS_ARENA / ZONE_NBR_ELEMENTS)


#define IS_TINY(x) (x <= TINY_BIN_SIZE)
#define IS_SMALL(x) (x > TINY_BIN_SIZE && x <= SMALL_BIN_SIZE)
#define IS_LARGE(x) (x > SMALL_BIN_SIZE)


# define ARENA_SIZE sizeof(t_arena)
# define BIN_SIZE sizeof(t_bin)

#define METADATA_SIZE(REQUESTED_SIZE) (BIN_SIZE + ARENA_SIZE + REQUESTED_SIZE)

#define ALIGN4(x) (((( (x) - 1) >> 2) << 2 ) + 4 + BIN_SIZE)

#define ALIGN8(x) (((( (x) - 1) >> 3) << 3) + 8 + BIN_SIZE)

typedef enum        e_bool
{
    FALSE,
    TRUE
}                   t_bool;

typedef struct s_bin {
    size_t		size;
    struct s_bin	*prev;
	struct s_bin	*next;
    t_bool        is_free;
    void           *valid_ptr;
}				t_bin;

// Memory zone types
typedef enum e_bins_type {
    TINY,
    SMALL,
    LARGE
} t_bins_type;

typedef struct	s_arena {
	// struct s_arena	*prev;
	struct s_arena	*next;
    struct s_arena *last;
    t_bins_type        bin_type;
	// size_t			total_size;
	size_t			free_size;
	// size_t			bins_count;
    t_bool          is_full;
}				t_arena;


extern t_arena *global_arena;

t_bool check_sys_limit(size_t size);
void* request_new_page_mmap(t_bins_type bins_type, size_t size) ;
void* my_malloc(size_t size) ;
t_bin* find_best_fit(t_bins_type binType, size_t size, t_arena **arena);
void split_bin(t_bin* bin, size_t size);



#endif