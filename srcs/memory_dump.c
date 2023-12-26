#include "../inc/malloc.h"

void print_arenas(int requested_size)
{
    ft_printf("requested_size = %d = 0x%x\n", requested_size, requested_size);
    ft_printf("sizeof(t_arena) = %zu = 0x%lx\n", sizeof(t_arena), sizeof(t_arena));
    ft_printf("sizeof(t_bin) = %zu = 0x%lx \n", sizeof(t_bin), sizeof(t_bin));
    ft_printf("sizeof(t_arena) + sizeof(t_bin) = %zu\n", sizeof(t_arena) + sizeof(t_bin));
    ft_printf("sizeof(t_bin) + requested_size = %zu\n\n", sizeof(t_bin) + requested_size);

  t_arena *current = global_arena;
  while (current)
  {
    ft_printf("arena = %p\n", current);
    ft_printf("arena->last = %p\n", current->last);
    int bins_type = current->bin_type;

    if (bins_type == TINY)
      ft_printf("arena->bin_type = TINY\n");
    else if (bins_type == SMALL)
      ft_printf("arena->bin_type = SMALL\n");
    else
      ft_printf("arena->bin_type = LARGE\n");

    ft_printf("arena->nbr_bins = %zu\n", current->allocated_bins_count);

    ft_printf("arena->free_size = %zu\n", current->free_size);
    ft_printf("\n");
    current = current->next;
  }
  ft_printf("===============================================\n");
}

void print_bins()
{
    t_arena *current = global_arena;
    int i = 1;
    while (current)
    {
        ft_printf("*******arena [%d] = %p *******\n", i++, current);
        t_bin *bin = (t_bin *)(current + 1);
        while (bin)
        {
            ft_printf("bin = %p\n", bin);
            ft_printf("bin->size = %zu = 0x%lx\n", bin->size, bin->size);
            char *is_free = bin->is_free ? "TRUE" : "FALSE";
            ft_printf("bin->is_free = %s\n", is_free);
            ft_printf("bin->magic_number = %u\n", bin->magic_number);
            ft_printf("bin->next = %p\n", bin->next);
            ft_printf("bin->prev = %p\n", bin->prev);
            ft_printf("\n");
            bin = bin->next;
        }
        current = current->next;
        ft_printf("===============================================\n");
    }
}