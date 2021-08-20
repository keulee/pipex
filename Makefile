NAME = pipex

SRCS = pipex.c \
		ft_putchar.c ft_putstr.c ft_exit_msg.c ft_split.c \
		ft_strlcpy.c ft_calloc.c ft_bzero.c ft_strjoin.c ft_strlen.c \
		ft_strncmp.c ft_get_path.c ft_free_tab2.c

OBJS = $(SRCS:.c=.o)

CC = clang

CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME) $(LIBFT)

re: fclean all

.PHONY: all clean fclean re