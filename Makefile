NAME	=	ft_malloc

CC		=	gcc

CFLAGS	=	-g #-Werror -Wextra -Wall

FUNCTIONS	=	best_fit.c\
				create_new_arena.c\
				dynamic_memory_api.c\
				find.c\
				free.c\
				hash_func.c\
				main.c\
				malloc.c\
				memory_dump.c\
				new_mmap.c\
				realloc.c\
				
				

HEADERS	=		inc/malloc.h

OBJDIR	=		objs

SRCDIR	=		srcs

OBJS	=		$(addprefix $(OBJDIR)/,$(FUNCTIONS:%.c=%.o))

LIBFT = libft/libft.a
LIBFTPRINTF = libft/ft_printf/libftprintf.a

all :			$(NAME)

$(OBJDIR):
				@echo "malloc Building............"
				@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(HEADERS)
				@$(CC) $(CFLAGS) -c $< -I./inc -o $@

$(LIBFT):
	@make -C libft

$(LIBFTPRINTF):
	@make -C libft/ft_printf

$(NAME): $(OBJDIR) $(OBJS) $(LIBFT) $(LIBFTPRINTF) $(HEADERS) 
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBFTPRINTF) -o $(NAME)
	@echo "\033[44m\033[93m\033[21mmalloc Built Successfully ............[OK]\033[49m\033[93m\n"

clean :
				@make clean -C libft
				@make clean -C libft/ft_printf
				@rm -rf $(OBJDIR)
				@echo "\033[41m\033[39m\033[1mRemoving malloc Objects...[OK]\033[49m\033[93m"

fclean :		clean
				@make fclean -C libft
				@make fclean -C libft/ft_printf
				@rm -rf $(NAME)

re :			fclean all
