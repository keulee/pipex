/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_child_parents.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keulee <keulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 20:11:10 by keulee            #+#    #+#             */
/*   Updated: 2021/09/07 00:42:43 by keulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	pipex_process(t_info *info, char **av, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_putendl_fd("fork failed", 2);
		exit(0);
	}
	else if (pid == 0)
		child_process(info, av, env);
	else if (pid > 0)
		parents_process(info, av, env, &pid);
}

void	child_process(t_info *info, char **av, char **env)
{
	info->fd_infile = open(av[1], O_RDONLY);
	if (info->fd_infile < 0)
	{
		ft_putendl_fd("file1(input) doesn't exist", 2);
		exit(1);
	}
	close(info->fd_pipe[0]); //pipe[0] -> read / pipe[1] -> write
	dup2(info->fd_pipe[1], STDOUT_FILENO); //0 : STDin, 1 : STDout
	close(info->fd_pipe[1]);
	dup2(info->fd_infile, STDIN_FILENO);
	// info->cmd_arg = ft_split(av[2], ' ');
	info->cmd_arg = parsing_str(av[2]);
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
		ft_putendl_fd("file2(output) doesn't exist", 2);
		exit(1);
	}
	close(info->fd_pipe[1]); //pipe[0] -> read / pipe[1] -> write
	dup2(info->fd_pipe[0], STDIN_FILENO);
	close(info->fd_pipe[0]);
	dup2(info->fd_outfile, STDOUT_FILENO);
	// info->cmd_arg = ft_split(av[3], ' ');
	info->cmd_arg = parsing_str(av[3]);
	info->path = part_path(env, info, info->cmd_arg[0]);
	if (execve(info->path, info->cmd_arg, env) == -1)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putendl_fd(info->cmd_arg[0], 2);
		ft_free(info);
		exit(1);
	}
}
