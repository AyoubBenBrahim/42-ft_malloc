#include "../inc/malloc.h"

void print_arenas() {
  t_arena *curr = g_arena;
  if (!curr) {
    ft_putstr("No Arenas\n");
    return;
  }
  ft_putstr("\n======== ARENAs GLOBAL HEADER = ");
  ft_putstr(to_hexa((uintptr_t)g_arena));
  ft_putstr(" =========\n\n");

  int i = 1;
  while (curr) {
    ft_putstr("******* Arena [");
    ft_putnbr(i++);
    ft_putstr("] ********\n");

  
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

    char *bin_type_str;
  
    if (curr->bin_type == TINY)
      bin_type_str = "TINY";
    else if (curr->bin_type == SMALL)
      bin_type_str = "SMALL";
    else
      bin_type_str = "LARGE";

    ft_putstr("arena->bin_type = ");
    ft_putstr(bin_type_str);
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

/*
*************************************************************************
*/

void print_bin(t_bin *bin) {
  if (!bin) {
    ft_putstr("NULL Bin\n");
    return;
  }
  ft_putstr("\n");
  ft_putstr("bin = ");
  ft_putstr(to_hexa((uintptr_t)bin));
  ft_putstr("\n");

  ft_putstr("bin->parent_arena = ");
  ft_putstr(to_hexa((uintptr_t)bin->parent_arena));
  ft_putstr("\n");

  ft_putstr("bin->size = ");
  ft_putnbr(bin->size);
  ft_putstr(" = ");
  ft_putstr(to_hexa((uintptr_t)bin->size));
  ft_putstr("\n");

  char *is_free = bin->is_free ? "TRUE" : "FALSE";
  ft_putstr("bin->is_free = ");
  ft_putstr(is_free);
  ft_putstr("\n");

  ft_putstr("bin->magic_number = ");
  ft_putstr(to_hexa((uintptr_t)bin->magic_number));
  ft_putstr("\n");

  ft_putstr("bin->next = ");
  ft_putstr(to_hexa((uintptr_t)bin->next));
  ft_putstr("\n");

  ft_putstr("bin->prev = ");
  ft_putstr(to_hexa((uintptr_t)bin->prev));
  ft_putstr("\n\n");
}

/*
*************************************************************************
*/

void print_bins() {
  t_arena *curr = g_arena;

  if (!curr) {
    ft_putstr("No Arenas\n");
    return;
  }

  int i = 1;
  while (curr) {
    char *bin_type_str;

    if (curr->bin_type == TINY)
      bin_type_str = "TINY";
    else if (curr->bin_type == SMALL)
      bin_type_str = "SMALL";
    else
      bin_type_str = "LARGE";

    ft_putstr("******* Arena [");
    ft_putnbr(i++);
    ft_putstr("] = ");
    ft_putstr(to_hexa((uintptr_t)curr));
    ft_putstr(" *******[");
    ft_putstr(bin_type_str);
    ft_putstr("]********\n ");


    ft_putstr(to_hexa((uintptr_t)curr->prev));
    ft_putstr(" --> ");
    ft_putstr(to_hexa((uintptr_t)curr));
    ft_putstr(" --> ");
    ft_putstr(to_hexa((uintptr_t)curr->next));
    ft_putstr("\n\n");

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
    ft_putstr(bin_type_str);
    ft_putstr("] bin====================\n\n");
  }
}

/*
*************************************************************************
*/


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

void print_header(t_bins_type bin_type) {
  t_arena *curr = g_arena;
  if (!curr) {
    return;
  }

  while (curr) {
    if (curr->bin_type != bin_type) {
      curr = curr->next;
      continue;
    }
    
    char *bin_type_str;
    if (bin_type == TINY)
      bin_type_str = "TINY";
    else if (bin_type == SMALL)
      bin_type_str = "SMALL";
    else
      bin_type_str = "LARGE";
    
    ft_putstr("\033[0;41m");
    ft_putstr(bin_type_str);
    ft_putstr(" : ");
    ft_putstr(to_hexa((uintptr_t)curr));
    ft_putstr("\033[0m\n");
    return;
  }
}

/*
*************************************************************************
*/

long show_alloc(t_bins_type bin_type)
{
  t_arena *curr = g_arena;
  if (!curr) {
    return 0;
  }

  print_header(bin_type);

  long total = 0;
  while (curr)
  {
    if (curr->bin_type != bin_type) {
      curr = curr->next;
      continue;
    }

    t_bin *bin = (t_bin *)(curr + 1);
    while (bin) {
      if (!bin->is_free) {
        ft_putstr(to_hexa((uintptr_t)bin));
        ft_putstr(" - ");
        ft_putstr(to_hexa((uintptr_t)bin + bin->size));
        ft_putstr(" : \033[0;32m");
        ft_putnbr(bin->size);
        ft_putstr(" \033[0mbytes\n");

        total += bin->size;
      }
      bin = bin->next;
    }
    curr = curr->next;
  }
  return total;
}

/*
*************************************************************************
*/

void show_alloc_mem()
{
    pthread_mutex_lock(&g_mallocMutex);
    long total = 0;
    total += show_alloc(TINY);
    total += show_alloc(SMALL);
    total += show_alloc(LARGE);
    ft_putstr("\nTotal : \033[0;32m");
    ft_putnbr(total);
    ft_putstr(" \033[0mbytes\n");
    pthread_mutex_unlock(&g_mallocMutex);
}
