/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keulee <keulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 20:14:33 by keulee            #+#    #+#             */
/*   Updated: 2021/09/07 00:42:17 by keulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_info {
	int		fd_infile;
	int		fd_outfile;
	int		fd_pipe[2];
	int		pid_status;
	char	*pathline;
	char	**env;
	char	*path;
	char	**cmd_arg;
}	t_info;

void	extract_pathline(char **env, t_info *info);
char	*part_path(char **env, t_info *info, char *cmd);
void	pipex_process(t_info *info, char **av, char **env);
void	child_process(t_info *info, char **av, char **env);
void	parents_process(t_info *info, char **av, char **env, pid_t *pid);
void	ft_free(t_info *info);

void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	ft_exit_msg(char *str);
void	free_tab2(char **str);
void	ft_putchar(const char c);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putstr(const char *str);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcpy(char *restrict dest, const char *restrict src, size_t size);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**parsing_str(char *str);
int	ft_tab_len(char const *s, char c, int i);
size_t count_bunch(char *str);

#endif
