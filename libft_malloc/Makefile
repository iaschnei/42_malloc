# ---------------------------------------------------------------------------- #

SRCS		=	malloc.c realloc.c free.c show_alloc_mem.c
# ---------------------------------------------------------------------------- #

OBJS		=	$(SRCS:.c=.o)

CC			=	gcc

INCL		=	libft_malloc.h

LIBFT		=	../libft/libft.a

FLAGS 	=	-g -fPIC -Wall -Wextra -Werror

ifeq ($(HOSTTYPE),)
		HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME		=	libft_malloc_$(HOSTTYPE).so

COLOR_GREEN	=	\033[1;32m
COLOR_RED	=	\033[1;31m
COLOR_BLUE	=	\033[3;36m
COLOR_PURP	=	\033[1;35m
COLOR_END	=	\033[0m

%.o: %.c
	@$(CC) $(FLAGS) -include $(INCL) -c $< -o $@
	@echo "$(COLOR_BLUE) || Compiling ($<)...$(COLOR_END)"

all: $(NAME)

$(LIBFT): $(INCL)
	@$(MAKE) -C ../libft
	@echo "$(COLOR_GREEN) || Compiled libft !$(COLOR_END)"

$(NAME): $(OBJS) $(INCL) $(LIBFT)
	@$(CC) -shared -o $(NAME) $(OBJS) $(LIBFT)
	@ln -s $(NAME) libft_malloc.so
	@echo "$(COLOR_GREEN) || Done !$(COLOR_END)"

clean:
	@rm -rf $(OBJS)
	@$(MAKE) -C ../libft clean
	@echo "$(COLOR_RED) || Cleaning files...$(COLOR_END)"

fclean: clean
	@rm -rf $(NAME) libft_malloc.so
	@$(MAKE) -C ../libft fclean
	@echo "$(COLOR_RED) || Cleaning library...$(COLOR_END)"

re: fclean all

.PHONY: re fclean all clean
