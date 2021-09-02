/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keulee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 20:20:07 by keulee            #+#    #+#             */
/*   Updated: 2021/09/02 20:20:09 by keulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>

# define BUFFER_SIZE 1

typedef struct s_info {
	int		fd_infile;
	int		fd_outfile;
	int		fd_pipe[2];
	int		pid_status;
	char	*pathline;
	char	**env;
	char	*path;
	char	**cmd_arg;
	int		h_flag;
}	t_info;

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
void	extract_pathline(char **env, t_info *info);
char	*part_path(char **env, t_info *info, char *cmd);
void	free_tab2(char **str);
void	ft_init(t_info *info, char **env);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	child_process(t_info *info, char **av, char **env);
void	parents_process(t_info *info, char **av, char **env, pid_t *pid);
void	pipex_process(t_info *info, char **av, char **env);
void	ft_free(t_info *info);
void	pipex_with_heredoc(t_info *info, char **av, char **env);
void	ft_heredoc(char **av, char **env, t_info *info);
int		get_next_line(int fd, char **line);
char	*ft_strdup(const char *src);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strchr(const char *s, int c);
void	ft_heredoc_parents(t_info *info, char **av, char **env, pid_t *pid);
void	heredoc_precess(int pipe_heredoc[2], char **av);
int		ft_strcmp(char *s1, char *s2);
void	heredoc_cmd_check(int ac, char **av, t_info *flag);

#endif
