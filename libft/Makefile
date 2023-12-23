# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayb***** <ayb*****@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/13 16:05:18 by ayb*****          #+#    #+#              #
#    Updated: 2020/01/25 20:16:46 by ayb*****         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

CFLAGS	=	-Werror -Wextra -Wall

SRCS	=	ft_abs.c\
			ft_atoi.c\
			ft_atoll.c\
			ft_bzero.c\
			ft_contains.c\
			ft_indexof.c\
			ft_isdigit.c\
			ft_islower.c\
			ft_isspace.c\
			ft_isupper.c\
			ft_ltoa.c\
			ft_memalloc.c\
			ft_memcmp.c\
			ft_memcpy.c\
			ft_memdel.c\
			ft_memset.c\
			ft_putchar.c\
			ft_putnbr.c\
			ft_putnchar.c\
			ft_putstr.c\
			ft_strcat.c\
			ft_strchr.c\
			ft_strcmp.c\
			ft_strcpy.c\
			ft_strdel.c\
			ft_strdup.c\
			ft_strjoin.c\
			ft_strjoin_free.c\
			ft_strlen.c\
			ft_strncmp.c\
			ft_strndup.c\
			ft_strnew.c\
			ft_strrchr.c\
			ft_strstr.c\
			ft_strsub.c\
			ft_strupper.c\
			ft_toupper.c\
			ft_tolower.c\
			ft_utoa.c\
			is_number.c\
			get_next_line.c\
			ft_strpbrk.c\
			is_in_range.c\

OBJDIR	=		objs

RED				=	\033[41m
GREEN			=	\033[42m
NC				=	\033[0m

OBJS	=	$(addprefix $(OBJDIR)/,$(SRCS:%.c=%.o))

HEADER	=	libft.h

# FT_PRINTF =	ft_printf/libftprintf.a

all : $(NAME)

$(OBJDIR):
			@echo "Libft Building............"
			@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o : %.c $(HEADER)
				@gcc $(CFLAGS) -c $< -o $@


$(NAME) : $(OBJDIR) $(OBJS)
	@/bin/rm -f a.out
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@echo "${GREEN}Libft Built Successfully ............[OK]${NC}\n"
# @make -C ft_printf

clean :
	@/bin/rm -rf $(OBJDIR)
	@echo "${RED}Cleaning Libft Objects...[OK]${NC}\n"
# @make clean -C ft_printf

fclean : clean
	@/bin/rm -f $(NAME)
	@echo "${RED}Libft...Cleaning All.......[OK]${NC}\n"
# @make fclean -C ft_printf

re : fclean all

