#include "../inc/malloc.h"
#include <stdio.h>
#include <stdlib.h>

// void print_headers_info(int requested_size) {
//     ft_printf("TINY_BIN_MAX = %zu\n", TINY_BIN_MAX);
//     ft_printf("SMALL_BIN_MAX = %zu\n", SMALL_BIN_MAX);
    
//   ft_printf("requested_size = %d = 0x%x\n", requested_size, requested_size);
//   ft_printf("sizeof(t_arena) = %zu = 0x%lx\n", sizeof(t_arena),
//             sizeof(t_arena));
//   ft_printf("sizeof(t_bin) = %zu = 0x%lx \n", sizeof(t_bin), sizeof(t_bin));
//   ft_printf("sizeof(t_arena) + sizeof(t_bin) = %zu\n",
//             sizeof(t_arena) + sizeof(t_bin));
//   ft_printf("sizeof(t_bin) + requested_size = %zu\n\n",
//             sizeof(t_bin) + requested_size);
// }


// void print_arena(t_arena *arena) {

//   ft_printf("arena->last = %p\n", arena->tail);
//   int bins_type = arena->bin_type;

//   if (bins_type == TINY)
//     ft_printf("arena->bin_type = TINY\n");
//   else if (bins_type == SMALL)
//     ft_printf("arena->bin_type = SMALL\n");
//   else
//     ft_printf("arena->bin_type = LARGE\n");

//   // ft_printf("arena->nbr_bins = %zu\n", arena->allocated_bins_count);

//   ft_printf("arena->free_size = %zu\n", arena->free_size);
//   ft_printf("\n");
// }

void print_arenas() {
  t_arena *curr = g_arena;
  if (!curr) {
    ft_putstr("No Arenas\n");
    return;
  }
  ft_putstr("======== ARENAs GLOBAL HEADER = ");
  ft_putstr(to_hexa((uintptr_t)g_arena));
  ft_putstr(" =========\n\n");

  while (curr) {
    ft_putstr("| ");
    ft_putstr(to_hexa((uintptr_t)curr->prev));
    ft_putstr(" --->| ** ");
    ft_putstr(to_hexa((uintptr_t)curr));
    ft_putstr(" ** --> | ");
    ft_putstr(to_hexa((uintptr_t)curr->next));
    ft_putstr(" |\n");

    ft_putstr("arena = ");
    ft_putstr(to_hexa((uintptr_t)curr));
    ft_putstr("\n");

    ft_putstr("arena->tail = ");
    ft_putstr(to_hexa((uintptr_t)curr->tail));
    ft_putstr("\n");

    char *bin_type = curr->bin_type == TINY    ? "TINY"
                     : curr->bin_type == SMALL ? "SMALL"
                                               : "LARGE";
    ft_putstr("arena->bin_type = ");
    ft_putstr(bin_type);
    ft_putstr("\n");
    ft_putstr("arena->mappped_size = ");
    ft_putnbr(curr->mapped_size);
    ft_putstr("\n");

    ft_putstr("arena->free_size = ");
    ft_putnbr(curr->free_size);
    ft_putstr("\n\n");
    curr = curr->next;
  }
  ft_putstr("===============================================\n");
}

// void print_bin(t_bin *bin) {
//   if (!bin) {
//     printf("NULL Bin\n");
//     return;
//   }
//   printf("\n");
//   printf("bin = %p\n", bin);
//   printf("bin->parent_arena = %p\n", bin->parent_arena);
//   printf("bin->size = %zu = 0x%lx\n", bin->size, bin->size);
//   char *is_free = bin->is_free ? "TRUE" : "FALSE";
//   printf("bin->is_free = %s\n", is_free);
//   printf("bin->magic_number = %u\n", bin->magic_number);
//   printf("bin->next = %p\n", bin->next);
//   printf("bin->prev = %p\n", bin->prev);
//   printf("\n");
// }

void print_bins() {
  t_arena *curr = g_arena;

  if (!curr) {
    ft_putstr("No Arenas\n");
    return;
  }

  int i = 1;
  while (curr) {
    char *bin_type = curr->bin_type == TINY    ? "TINY"
                     : curr->bin_type == SMALL ? "SMALL"
                                               : "LARGE";

    ft_putstr("******* Arena [");
    ft_putnbr(i++);
    ft_putstr("] = ");
    ft_putstr(to_hexa((uintptr_t)curr));
    ft_putstr(" *******[");
    ft_putstr(bin_type);
    ft_putstr("]********\n ");


    ft_putstr(to_hexa((uintptr_t)curr->prev));
    ft_putstr(" --> ");
    ft_putstr(to_hexa((uintptr_t)curr));
    ft_putstr(" --> ");
    ft_putstr(to_hexa((uintptr_t)curr->next));
    ft_putstr("\n");

    t_bin *bin = (t_bin *)(curr + 1);
    int j = 1;
    while (bin) {
      ft_putstr(" bin [");
      ft_putnbr(j++);
      ft_putstr("] = ");
      ft_putstr(to_hexa((uintptr_t)bin));
      ft_putstr("\n");

      ft_putstr(" bin->parent_arena = ");
      ft_putstr(to_hexa((uintptr_t)bin->parent_arena));
      ft_putstr("\n");

      ft_putstr(" bin->size = ");
      ft_putnbr(bin->size);
      ft_putstr(" = ");
      ft_putstr(to_hexa((uintptr_t)bin->size));
      ft_putstr("\n");


      char *is_free = bin->is_free ? "TRUE" : "FALSE";
      ft_putstr(" bin->is_free = ");
      ft_putstr(is_free);
      ft_putstr("\n");

      ft_putstr(" bin->magic_number = ");
      ft_putstr(to_hexa((uintptr_t)bin->magic_number));
      ft_putstr("\n");

      ft_putstr(" bin->next = ");
      ft_putstr(to_hexa((uintptr_t)bin->next));
      ft_putstr("\n");

      ft_putstr(" bin->prev = ");
      ft_putstr(to_hexa((uintptr_t)bin->prev));
      ft_putstr("\n");

      ft_putstr("\n");

      bin = bin->next;
    }
    curr = curr->next;

    ft_putstr("====================END OF [");
    ft_putstr(bin_type);
    ft_putstr("] bin====================\n");
  }
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

int show_alloc(t_bins_type bin_type)
{
  t_arena *curr = g_arena;
  if (!curr) {
    return 0;
  }

// char *bin_type1 = bin_type == TINY    ? "TINY"
//                      : curr->bin_type == SMALL ? "SMALL"
//                                                : "LARGE";

// if (bin_type == TINY)
//   printf("TINY : \n");
// else if (bin_type == SMALL)
//   printf("SMALL : \n");
// else if (bin_type == LARGE)
//   printf("LARGE : \n");

//   // printf("bin_type1 = %s\n", bin_type1);
//   return 0;

  int total = 0;
  while (curr)
  {
    if (curr->bin_type != bin_type) {
      curr = curr->next;
      continue;
    }
    char *bin_type;
    if (curr->bin_type == TINY)
      bin_type = "TINY";
    else if (curr->bin_type == SMALL)
      bin_type = "SMALL";
    else
      bin_type = "LARGE";

    ft_putstr(bin_type);
    ft_putstr(" : ");
    ft_putstr(to_hexa((uintptr_t)curr));
    ft_putstr("\n");

    t_bin *bin = (t_bin *)(curr + 1);
    while (bin) {
      if (!bin->is_free) {
        ft_putstr(to_hexa((uintptr_t)bin));
        ft_putstr(" - ");
        ft_putstr(to_hexa((uintptr_t)bin + bin->size));
        ft_putstr(" : ");
        ft_putnbr(bin->size);
        ft_putstr(" bytes\n");

        total += bin->size;
      }
      bin = bin->next;
    }
    curr = curr->next;
  }
  return total;
}

void show_alloc_mem()
{
    pthread_mutex_lock(&g_mallocMutex);
    int total = 0;
    total += show_alloc(TINY);
    total += show_alloc(SMALL);
    total += show_alloc(LARGE);
    ft_putstr("Total : ");
    ft_putnbr(total);
    ft_putstr(" bytes\n");
    pthread_mutex_unlock(&g_mallocMutex);
}