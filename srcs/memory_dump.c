#include "../inc/malloc.h"

void print_headers_info(int requested_size) {
    ft_printf("TINY_BIN_MAX = %zu\n", TINY_BIN_MAX);
    ft_printf("SMALL_BIN_MAX = %zu\n", SMALL_BIN_MAX);
    
  ft_printf("requested_size = %d = 0x%x\n", requested_size, requested_size);
  ft_printf("sizeof(t_arena) = %zu = 0x%lx\n", sizeof(t_arena),
            sizeof(t_arena));
  ft_printf("sizeof(t_bin) = %zu = 0x%lx \n", sizeof(t_bin), sizeof(t_bin));
  ft_printf("sizeof(t_arena) + sizeof(t_bin) = %zu\n",
            sizeof(t_arena) + sizeof(t_bin));
  ft_printf("sizeof(t_bin) + requested_size = %zu\n\n",
            sizeof(t_bin) + requested_size);
}

/*
TINY : 0xA0000
0xA0020 - 0xA004A : 42 bytes
0xA006A - 0xA00BE : 84 bytes
SMALL : 0xAD000
0xAD020 - 0xADEAD : 3725 bytes
LARGE : 0xB0000
0xB0020 - 0xBBEEF : 48847 bytes
Total : 52698 bytes
*/

void show_alloc()
{
   t_arena *curr = global_arena;
  if (!curr) {
    ft_printf("No Arenas\n");
    return;
  }
int total = 0;
 while (curr)
 {
    char *bin_type = curr->bin_type == TINY ? "TINY" : curr->bin_type == SMALL ? "SMALL" : "LARGE";
    ft_printf("%s : 0x%lx\n", bin_type, (size_t)curr);
    t_bin *bin = (t_bin *)(curr + 1);
    while (bin)
    {
      if (!bin->is_free)
      {
        ft_printf("0x%lx - 0x%lx : %zu bytes\n", (size_t)bin, (size_t)bin + bin->size, bin->size);
        total += bin->size;
      }
      bin = bin->next;
    }
    curr = curr->next;
 }
  ft_printf("Total : %d bytes\n", total);


}

void print_arena(t_arena *arena) {

  ft_printf("arena->last = %p\n", arena->tail);
  int bins_type = arena->bin_type;

  if (bins_type == TINY)
    ft_printf("arena->bin_type = TINY\n");
  else if (bins_type == SMALL)
    ft_printf("arena->bin_type = SMALL\n");
  else
    ft_printf("arena->bin_type = LARGE\n");

  // ft_printf("arena->nbr_bins = %zu\n", arena->allocated_bins_count);

  ft_printf("arena->free_size = %zu\n", arena->free_size);
  ft_printf("\n");
}

void print_arenas() {
  t_arena *curr = global_arena;
  if (!curr) {
    ft_printf("No Arenas\n");
    return;
  }
  ft_printf("============= ARENAs GLOBAL HEADER = %p ===========\n\n", global_arena);
  while (curr) {
    ft_printf("| %p --->| ** %p ** --> | %p |\n", curr->prev, curr, curr->next);
    ft_printf("arena = %p\n", curr);
    ft_printf("arena->tail = %p\n", curr->tail);
    int bins_type = curr->bin_type;

    if (bins_type == TINY)
      ft_printf("arena->bin_type = TINY\n");
    else if (bins_type == SMALL)
      ft_printf("arena->bin_type = SMALL\n");
    else
      ft_printf("arena->bin_type = LARGE\n");

    // ft_printf("arena->nbr_bins = %zu\n", curr->allocated_bins_count);

    ft_printf("arena->mappped_size = %zu\n", curr->mapped_size);
    ft_printf("arena->free_size = %zu\n", curr->free_size);
    ft_printf("\n");
    curr = curr->next;
  }
  ft_printf("===============================================\n");
}

void print_bin(t_bin *bin) {
  if (!bin) {
    ft_printf("NULL Bin\n");
    return;
  }
  ft_printf("\n");
  ft_printf("bin = %p\n", bin);
  ft_printf("bin->parent_arena = %p\n", bin->parent_arena);
  ft_printf("bin->size = %zu = 0x%lx\n", bin->size, bin->size);
  char *is_free = bin->is_free ? "TRUE" : "FALSE";
  ft_printf("bin->is_free = %s\n", is_free);
  ft_printf("bin->magic_number = %u\n", bin->magic_number);
  ft_printf("bin->next = %p\n", bin->next);
  ft_printf("bin->prev = %p\n", bin->prev);
  ft_printf("\n");
}

void print_bins() {
  t_arena *curr = global_arena;

  if (!curr) {
    ft_printf("No Arenas\n");
    return;
  }

  int i = 1;
  while (curr) {
  char *bin_type;
  if (curr->bin_type == TINY)
    bin_type = "TINY";
  else if (curr->bin_type == SMALL)
    bin_type = "SMALL";
  else
    bin_type = "LARGE";
    ft_printf("*******arena [%d] = %p *******[%s]********\n", i++, curr, bin_type);
    ft_printf("%p --> %p --> %p\n", curr->prev, curr, curr->next);

    t_bin *bin = (t_bin *)(curr + 1);
    int j = 1;
    while (bin) {
      ft_printf(" bin [%d] = %p\n", j++, bin);
      ft_printf(" bin->parent_arena = %p\n", bin->parent_arena);
      ft_printf(" bin->size = %zu = 0x%lx\n", bin->size, bin->size);
      char *is_free = bin->is_free ? "TRUE" : "FALSE";
      ft_printf(" bin->is_free = %s\n", is_free);
      ft_printf(" bin->magic_number = %u\n", bin->magic_number);
      ft_printf(" bin->next = %p\n", bin->next);
      ft_printf(" bin->prev = %p\n", bin->prev);
      ft_printf("\n");
      bin = bin->next;
    }
    curr = curr->next;
    ft_printf("====================END OF [%s] bin====================\n", bin_type);
  }
}