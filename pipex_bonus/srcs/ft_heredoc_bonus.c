#include "../includes/pipex_bonus.h"

void	pipex_with_heredoc(t_info *info, char **av, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_putstr_fd("fork failed\n", 2);
	else if (pid == 0)
	{
		if (ft_strncmp(av[1], "here_doc", 8) == 0)
			ft_heredoc(av, env, info);
		else
			child_process(info, av, env);
	}
	else if (pid > 0)
	{
		if (ft_strncmp(av[1], "here_doc", 8) == 0)
			ft_heredoc_parents(info, av, env, &pid);
		else
			parents_process(info, av, env, &pid);
	}
}

void	ft_heredoc(char **av, char **env, t_info *info)
{
	int		pipe_heredoc[2];

	heredoc_precess(pipe_heredoc, av);
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

void	heredoc_precess(int pipe_heredoc[2], char **av)
{
	char	*line;

	if (pipe(pipe_heredoc) == -1)
	{
		ft_putstr_fd("pipe failed\n", 2);
		exit(1);
	}
	write(STDOUT_FILENO, "pipe heredoc> ", 14);
	while (get_next_line(0, &line) != 0)
	{
		if (ft_strcmp(line, av[2]) == 0)
		{
			free(line);
			break ;
		}
		write(STDOUT_FILENO, "pipe heredoc> ", 14);
		write(pipe_heredoc[1], line, ft_strlen(line));
		write(pipe_heredoc[1], "\n", 1);
		free(line);
	}
}

void	ft_heredoc_parents(t_info *info, char **av, char **env, pid_t *pid)
{
	waitpid(*pid, &info->pid_status, WNOHANG);
	info->fd_outfile = open(av[5], O_RDWR | O_CREAT | O_APPEND, 0644);
	if (info->fd_outfile < 0)
	{
		ft_putstr_fd("output file doesn't exist\n", 2);
		exit(1);
	}
	close(info->fd_pipe[1]);
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
