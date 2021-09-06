# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: keulee <keulee@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/02 20:14:38 by keulee            #+#    #+#              #
#    Updated: 2021/09/07 01:48:50 by keulee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = srcs/pipex.c \
		 srcs/ft_get_path.c \
		 srcs/ft_free.c \
		 srcs/ft_pipex_child_parents.c \
		 srcs/ft_bzero.c srcs/ft_calloc.c srcs/ft_exit_msg.c \
		 srcs/ft_free_tab2.c srcs/ft_putchar.c srcs/ft_putchar_fd.c \
		 srcs/ft_putendl_fd.c srcs/ft_putstr.c srcs/ft_putstr_fd.c \
		 srcs/ft_split.c srcs/ft_strjoin.c srcs/ft_strlcpy.c srcs/ft_strlen.c \
		 srcs/ft_strncmp.c srcs/ft_parsing_path.c srcs/ft_parsing_path_utiles.c
	

OBJS = $(SRCS:.c=.o)

CC = clang

CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address

RM = rm -f

all: $(NAME)

bonus: re
	@$(MAKE) fclean -C pipex_bonus
	@$(MAKE) -C pipex_bonus
	@cp ./pipex_bonus/pipex ./pipex

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	@$(MAKE) -C pipex_bonus clean
	@$(RM) $(OBJS)

fclean: clean
	@$(MAKE) -C pipex_bonus fclean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
