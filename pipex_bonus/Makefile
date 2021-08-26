NAME = pipexb

SRCS = pipex_bonus.c \
		ft_putstr_fd.c ft_putchar_fd.c ft_putendl_fd.c ft_split.c ft_get_path.c \
		ft_free.c ft_calloc.c ft_strjoin.c ft_strlcpy.c ft_strncmp.c ft_bzero.c ft_strlen.c \
		ft_exit_msg.c ft_putchar.c ft_putstr.c ft_pipex_child_parents.c \
		ft_heredoc.c get_next_line.c ft_substr.c ft_strchr.c ft_strdup.c
	

OBJS = $(SRCS:.c=.o)

CC = clang

CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME) $(LIBFT)

.PHONY: fclean all