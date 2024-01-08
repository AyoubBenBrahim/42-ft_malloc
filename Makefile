ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
DYNAMIC_LIB = libft_malloc.so

CC = gcc
CFLAGS = -Werror -Wextra -Wall -fPIC
FUNCTIONS = best_fit.c create_new_arena.c dynamic_memory_api.c free.c hash_func.c main.c malloc.c memory_dump.c new_mmap.c realloc.c calloc.c
HEADERS = inc/malloc.h
OBJDIR = objs
SRCDIR = srcs
OBJS = $(addprefix $(OBJDIR)/,$(FUNCTIONS:%.c=%.o))
LIBFT = libft/libft.a
LIBFTPRINTF = libft/ft_printf/libftprintf.a

all: $(NAME)

$(OBJDIR):
	@echo "malloc Building............"
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -I./inc -o $@

$(LIBFT):
	@make -C libft

$(LIBFTPRINTF):
	@make -C libft/ft_printf

$(NAME): $(OBJDIR) $(OBJS) $(LIBFT) $(LIBFTPRINTF) $(HEADERS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBFTPRINTF) -shared -o $(NAME)
	@ln -sf $(NAME) $(DYNAMIC_LIB)
	@echo "\033[44m\033[93m\033[21mmalloc lib Built Successfully ............[OK]\033[49m\033[93m\n"

clean:
	@make clean -C libft
	@make clean -C libft/ft_printf
	@rm -rf $(OBJDIR)
	@echo "\033[41m\033[39m\033[1mRemoving malloc lib Objects...[OK]\033[49m\033[93m"

fclean: clean
	@make fclean -C libft
	@make fclean -C libft/ft_printf
	@rm -rf $(NAME)
	@rm -rf $(DYNAMIC_LIB)

re: fclean all

.PHONY: all clean fclean re