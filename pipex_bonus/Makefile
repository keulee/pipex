NAME = pipexb

SRCS = pipex_bonus.c \
		ft_putstr_fd.c ft_putchar_fd.c
	

OBJS = $(SRCS:.c=.o)

CC = clang

CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME) $(LIBFT)

.PHONY: fclean all