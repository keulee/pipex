NAME = pipex

SRCS = pipex.c \
		ft_putchar.c ft_putstr.c ft_exit_msg.c ft_split.c \
		ft_strlcpy.c ft_calloc.c ft_bzero.c ft_strjoin.c ft_strlen.c \
		ft_strncmp.c ft_get_path.c ft_free.c \
		ft_putstr_fd.c ft_putendl_fd.c ft_putchar_fd.c ft_pipex_child_parents.c
	

OBJS = $(SRCS:.c=.o)

CC = clang

CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

bonus: re
	$(MAKE) fclean -C pipex_bonus
	$(MAKE) -C pipex_bonus
	cp ./pipex_bonus/pipexb ./pipexb

clean:
	$(MAKE) -C pipex_bonus clean
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C pipex_bonus fclean
	$(RM) $(NAME) $(LIBFT) pipexb

re: fclean all

.PHONY: all clean fclean re