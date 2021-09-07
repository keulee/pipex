# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: keulee <keulee@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/02 20:20:12 by keulee            #+#    #+#              #
#    Updated: 2021/09/07 01:56:39 by keulee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = srcs/pipex_bonus.c \
		srcs/ft_putstr_fd_bonus.c srcs/ft_putchar_fd_bonus.c \
		srcs/ft_putendl_fd_bonus.c srcs/ft_split_bonus.c \
		srcs/ft_get_path_bonus.c srcs/ft_free_bonus.c srcs/ft_calloc_bonus.c \
		srcs/ft_strjoin_bonus.c srcs/ft_strlcpy_bonus.c \
		srcs/ft_strncmp_bonus.c srcs/ft_bzero_bonus.c srcs/ft_strlen_bonus.c \
		srcs/ft_exit_msg_bonus.c srcs/ft_putchar_bonus.c \
		srcs/ft_putstr_bonus.c srcs/ft_pipex_child_parents_bonus.c \
		srcs/ft_heredoc_bonus.c srcs/get_next_line_bonus.c \
		srcs/ft_substr_bonus.c srcs/ft_strchr_bonus.c srcs/ft_strdup_bonus.c \
		srcs/ft_strcmp_bonus.c srcs/ft_parsing_path_bonus.c \
		srcs/ft_parsing_path_utiles_bonus.c

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
