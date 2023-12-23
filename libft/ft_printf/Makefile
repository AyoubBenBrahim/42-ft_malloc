

NAME	=	libftprintf.a

CFLAGS	=	-Werror -Wextra -Wall

SRCS	=	ft_poubx.c\
	  		ft_print_c.c\
	  		ft_print_d.c\
	 		ft_print_f.c\
	 		ft_print_s.c\
	  		split_float.c\
			ft_base.c\
			ft_large_pow.c\
			ft_precision.c\
			ft_printf.c\
			ft_width.c\
			initialize_args.c\
			multiply_string.c\
			padd.c\
			shift_bits.c\
			sum_string.c\
			va_arg_getter.c\
			utils.c\
			parse.c\
			color.c

HEADERS	=	inc/ft_printf.h inc/dispatcher.h inc/color.h

OBJDIR	=	objs

SRCDIR	=	src

OBJS	=	$(addprefix $(OBJDIR)/,$(SRCS:%.c=%.o))

LFT		= 	../libft.a

all : $(NAME)

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(HEADERS)
	@printf "\033[32m\033[1m"
	@gcc $(CFLAGS)   -c $< -I./inc -o $@

$(OBJDIR):
	@echo "ft_printf Building............"
	@mkdir -p $(OBJDIR)


$(NAME) : $(LFT) $(OBJDIR) $(OBJS)
	@/bin/rm -f a.out
	@cp $(LFT) .
	@mv libft.a $(NAME)
	@ar rcs $(NAME) $(OBJS)
	@ranlib $(NAME)
	@echo "\033[44m\033[93m\033[21mft_printf Built Successfully ............[OK]\033[49m\033[93m\n"


clean :
	@rm -rf $(OBJDIR)
	@echo "\033[41m\033[39m\033[1mRemoving ft_printf objects...[OK]\033[49m\033[93m\n"

fclean : clean
	@rm -rf $(NAME)
	@echo "\033[41m\033[39m\033[1mft_printf: Removing All...[OK]\033[49m\033[93m\n"

re : fclean all

.PHONY: clean fclean all re
