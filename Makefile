# to test the shared lib uncomment the NAME and DYNAMIC_LIB variables and comment the SHARED variable, use CLIBFLAGS
# remove the main.c

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

# NAME		=	libft_malloc_$(HOSTTYPE).so
NAME 		=	ft_malloc
DYNAMIC_LIB =	libft_malloc.so

CC			=	gcc

CFLAGS		=	-Werror -Wextra -Wall -g
CLIBFLAGS	=	-Werror -Wextra -Wall -g -fPIC
SHARED		=   #-shared

FUNCTIONS	=	best_fit.c \
				calloc.c \
				create_new_arena.c \
				free.c \
				hash_func.c \
				helpers.c \
				malloc.c \
				memory_dump.c \
				new_mmap.c \
				realloc.c \
				reallocf.c\
				main.c
				

HEADERS		=	inc/malloc.h
OBJDIR		=	objs
SRCDIR		=	srcs
OBJS		=	$(addprefix $(OBJDIR)/,$(FUNCTIONS:%.c=%.o))

all			:	$(NAME)

$(OBJDIR)	:
				@echo "malloc Building............"
				@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o:	$(SRCDIR)/%.c $(HEADERS)
				@$(CC) $(CFLAGS) -c $< -I./inc -o $@ 

$(NAME)		:	$(OBJDIR) $(OBJS) $(HEADERS)
				@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(SHARED)
				@rm -rf $(DYNAMIC_LIB)
#				@ln -s $(NAME) $(DYNAMIC_LIB)
				@echo "\033[44m\033[93m\033[21mmalloc lib Built Successfully ............[OK]\033[49m\033[93m\n"

clean		:
				@rm -rf $(OBJDIR)
				@echo "\033[41m\033[39m\033[1mRemoving malloc lib Objects...[OK]\033[49m\033[93m"

fclean		:	clean
				@rm -rf $(NAME)
				@rm -rf $(DYNAMIC_LIB)
				@rm -rf *.so
				@rm -rf *dSYM

re			:	fclean all

.PHONY		:	all clean fclean re