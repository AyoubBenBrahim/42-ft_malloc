



// Basic block structure
typedef struct block {
    size_t size;
    struct block* next;
    int free;
    // Add more fields if needed
} block_t;

// Size of block metadata
#define BLOCK_SIZE sizeof(block_t)


// Head of the free list
static block_t* free_list = NULL;

// Pre-allocated memory zones
static void* tiny_zone = NULL;
static void* small_zone = NULL;
static size_t tiny_zone_size = 0;
static size_t small_zone_size = 0;

// Page size
static size_t page_size = 0;

// Function to split a block if it is large enough
void split_block(block_t* block, size_t size) {
    block_t* new_block = (block_t*)((char*)block + BLOCK_SIZE + size);
    new_block->size = block->size - size - BLOCK_SIZE;
    new_block->next = block->next;
    new_block->free = 1;
    block->size = size;
    block->next = new_block;
    block->free = 0;
}





// Function to free memory using munmap()
void mmap_free(void* ptr, size_t size) {
    block_t* block = (block_t*)((char*)ptr - BLOCK_SIZE);
    munmap(block, size + BLOCK_SIZE);
}

// Function to get the page size
size_t get_page_size() {
    if (page_size == 0)
        page_size = sysconf(_SC_PAGESIZE);

    return page_size;
}

// Function to align the size to the nearest multiple of the page size
size_t align_size(size_t size) {
    size_t page_size = get_page_size();
    size_t remainder = size % page_size;
    if (remainder == 0)
        return size;
    else
        return size + page_size - remainder;
}



// Function to find the best-fit block for allocation
block_t* find_best_fit(size_t size) {
    block_t* current = free_list;
    block_t* best_fit = NULL;
    size_t best_fit_size = -1;

    while (current) {
        if (current->free && current->size >= size) {
            if (current->size == size)
                return current;
            else if (current->size < best_fit_size) {
                best_fit = current;
                best_fit_size = current->size;
            }
        }
        current = current->next;
    }

    return best_fit;
}

// Function to allocate memory
void* malloc(size_t size) {
    if (size <= 0)
        return NULL;

    // Align the size to the nearest multiple of the page size
    size = align_size(size);

    // Check if the allocation is tiny or small
    if (size <= tiny_zone_size) {
        // Allocate from the tiny zone
        if (!tiny_zone)
            tiny_zone = request_new_page_mmap(tiny_zone_size);

        return request_new_page_mmap(size);
    } else if (size <= small_zone_size) {
        // Allocate from the small zone
        if (!small_zone)
            small_zone = request_new_page_mmap(small_zone_size);

        return request_new_page_mmap(size);
    }

    // Find the best-fit block for large allocations
    block_t* best_fit = find_best_fit(size);

   // If a suitable block is found, allocate from it
    if (best_fit) {
        // Split the block if it is large enough
        if (best_fit->size >= size + BLOCK_SIZE)
            split_block(best_fit, size);

        best_fit->free = 0;
        return (void*)((char*)best_fit + BLOCK_SIZE);
    }

    // If no suitable block is found, allocate a new block using mmap()
    size_t alloc_size = align_size(size + BLOCK_SIZE);
    block_t* new_block = (block_t*)request_new_page_mmap(alloc_size);
    if (!new_block)
        return NULL;

    new_block->size = size;
    new_block->next = NULL;
    new_block->free = 0;

    // Add the new block to the free list
    if (!free_list)
        free_list = new_block;
    else {
        block_t* current = free_list;
        while (current->next)
            current = current->next;
        current->next = new_block;
    }

    return (void*)((char*)new_block + BLOCK_SIZE);
}



// Function to initialize the memory zones
void init_zones(size_t tiny_size, size_t small_size) {
    tiny_zone_size = align_size(tiny_size);
    small_zone_size = align_size(small_size);
}

// Function to release the memory zones
void release_zones() {
    if (tiny_zone)
        mmap_free(tiny_zone, tiny_zone_size);

    if (small_zone)
        mmap_free(small_zone, small_zone_size);
}
















