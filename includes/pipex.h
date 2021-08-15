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
	int pid_status;
	char **env;
	char *path1;
	char *path2;
	char **cmd1;
	char **cmd2;
}			t_info;

void	ft_exit_msg(char *str);
void	ft_putchar(const char c);
void	ft_putstr(const char *str);

#endif