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
	char *pathline;
	char **env;
	// char **tmp_path[5];
	char *path;
	// char *path2;
	// char *path2;
	char **cmd_arg1;
	char **cmd_arg2;
}			t_info;

void	ft_exit_msg(char *str);
void	ft_putchar(const char c);
void	ft_putstr(const char *str);
char	**ft_split(char const *s, char c);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlcpy(char *restrict dest, const char *restrict src, size_t size);
void	ft_bzero(void *s, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif