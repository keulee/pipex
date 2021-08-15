#ifndef PIPEX_H
# define PIPEX_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>

typedef	struct s_info{
	int fd_infile;
	int fd_outfile;
	int	fd_pipe[2];
}			t_info;

void	ft_exit_msg(char *str);
void	ft_putchar(char c);
void	ft_putstr(char *str);

#endif