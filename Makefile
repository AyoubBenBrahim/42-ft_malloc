NAME	=	ft_nm

CC		=	gcc

CFLAGS	=	-Werror -Wextra -Wall

FUNCTIONS	=	ft_nm.c\
				manageELF32.c\
				manageELF64.c\
				printer.c\
				symboles_handler.c\
				debug.c\
				get_section_name.c\
				
				

HEADERS	=		inc/ft_nm.h

OBJDIR	=		objs

SRCDIR	=		srcs

OBJS	=		$(addprefix $(OBJDIR)/,$(FUNCTIONS:%.c=%.o))

LIBFT = libft/libft.a
LIBFTPRINTF = libft/ft_printf/libftprintf.a

all :			$(NAME)

$(OBJDIR):
				@echo "FT_NM Building............"
				@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(HEADERS)
				@$(CC) $(CFLAGS) -c $< -I./inc -o $@

$(LIBFT):
	@make -C libft

$(LIBFTPRINTF):
	@make -C libft/ft_printf

$(NAME): $(OBJDIR) $(OBJS) $(LIBFT) $(LIBFTPRINTF) $(HEADERS) 
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBFTPRINTF) -o $(NAME)
	@echo "\033[44m\033[93m\033[21mFT_NM Built Successfully ............[OK]\033[49m\033[93m\n"

clean :
				@make clean -C libft
				@make clean -C libft/ft_printf
				@rm -rf $(OBJDIR)
				@echo "\033[41m\033[39m\033[1mRemoving FT_NM Objects...[OK]\033[49m\033[93m"

fclean :		clean
				@make fclean -C libft
				@make fclean -C libft/ft_printf
				@rm -rf $(NAME)

re :			fclean all
