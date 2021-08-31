#include "../includes/pipex_bonus.h"

void	child_process(t_info *info, char **av, char **env)
{
	info->fd_infile = open(av[1], O_RDONLY);
	if (info->fd_infile < 0)
	{
		ft_putstr_fd("file1(input) doesn't exist\n", 2);
		exit(1);
	}
	close(info->fd_pipe[0]);
	dup2(info->fd_pipe[1], STDOUT_FILENO);
	close(info->fd_pipe[1]);
	dup2(info->fd_infile, STDIN_FILENO);
	info->cmd_arg = ft_split(av[2], ' ');
	info->path = part_path(env, info, info->cmd_arg[0]);
	if (execve(info->path, info->cmd_arg, env) == -1)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putendl_fd(info->cmd_arg[0], 2);
		exit(1);
	}
}

void	parents_process(t_info *info, char **av, char **env, pid_t *pid)
{
	waitpid(*pid, &info->pid_status, WNOHANG);
	info->fd_outfile = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (info->fd_outfile < 0)
	{
		ft_putstr_fd("file2(output) doesn't exist\n", 2);
		exit(1);
	}
	close(info->fd_pipe[1]);
	dup2(info->fd_pipe[0], STDIN_FILENO);
	close(info->fd_pipe[0]);
	dup2(info->fd_outfile, STDOUT_FILENO);
	info->cmd_arg = ft_split(av[3], ' ');
	info->path = part_path(env, info, info->cmd_arg[0]);
	if (execve(info->path, info->cmd_arg, env) == -1)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putendl_fd(info->cmd_arg[0], 2);
		ft_free(info);
		exit(1);
	}
}
