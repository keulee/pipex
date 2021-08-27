#include "includes/pipex_bonus.h"

void	ft_heredoc(char **av, char **env, t_info *info)
{
	int		pipe_heredoc[2];
	char	*line;

	if (pipe(pipe_heredoc) == -1)
	{
		ft_putstr_fd("pipe failed", 2);
		exit(1);
	}
	write(1, "pipe heredoc> ", 14);
	while (get_next_line(0, &line) > 0)
	{
		if (ft_strncmp(line, av[2], ft_strlen(line)) == 0)
		{
			free(line);
			break ;
		}
		write(STDOUT_FILENO, "pipe heredoc> ", 14);
		write(pipe_heredoc[1], line, ft_strlen(line));
		write(pipe_heredoc[1], "\n", 1);
		free(line);
	}
	dup2(pipe_heredoc[0], STDIN_FILENO);
	close(pipe_heredoc[1]);
	dup2(info->fd_pipe[1], STDOUT_FILENO);
	close(info->fd_pipe[0]);
	info->cmd_arg = ft_split(av[3], ' ');
	info->path = part_path(env, info, info->cmd_arg[0]);
	if (execve(info->path, info->cmd_arg, env) == -1)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putendl_fd(info->cmd_arg[0], 2);
		exit(1);
	}
}

void	ft_heredoc_parents(t_info *info, char **av, char **env, pid_t *pid)
{
	waitpid(*pid, &info->pid_status, WNOHANG);
	info->fd_outfile = open(av[5], O_RDWR | O_CREAT | O_APPEND, 0777);
	if (info->fd_outfile < 0)
	{
		ft_putstr_fd("output file doesn't exist", 2);
		exit(1);
	}
	close(info->fd_pipe[1]); //pipe[0] -> read / pipe[1] -> write
	dup2(info->fd_pipe[0], STDIN_FILENO);
	close(info->fd_pipe[0]);
	dup2(info->fd_outfile, STDOUT_FILENO);
	info->cmd_arg = ft_split(av[4], ' ');
	info->path = part_path(env, info, info->cmd_arg[0]);
	if (execve(info->path, info->cmd_arg, env) == -1)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putendl_fd(info->cmd_arg[0], 2);
		ft_free(info);
		exit(1);
	}
}