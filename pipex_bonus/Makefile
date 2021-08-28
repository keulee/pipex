NAME = pipex

SRCS = pipex_bonus.c \
		srcs/ft_putstr_fd.c srcs/ft_putchar_fd.c srcs/ft_putendl_fd.c srcs/ft_split.c srcs/ft_get_path.c \
		srcs/ft_free.c srcs/ft_calloc.c srcs/ft_strjoin.c srcs/ft_strlcpy.c srcs/ft_strncmp.c srcs/ft_bzero.c srcs/ft_strlen.c \
		srcs/ft_exit_msg.c srcs/ft_putchar.c srcs/ft_putstr.c srcs/ft_pipex_child_parents.c \
		srcs/ft_heredoc.c srcs/get_next_line.c srcs/ft_substr.c srcs/ft_strchr.c srcs/ft_strdup.c \
		ft_strcmp.c
	

OBJS = $(SRCS:.c=.o)

CC = clang

CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME) $(LIBFT)

.PHONY: fclean all