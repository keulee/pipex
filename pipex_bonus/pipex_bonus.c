#include "includes/pipex_bonus.h"

void	ft_free(t_info *info)
{
	free(info->path);
	free_tab2(info->cmd_arg);
	info->path = NULL;
	info->cmd_arg = NULL;
}

int	main(int ac, char **av, char **env)
{
	t_info	info;
	int		i;
	pid_t	pid;

	i = 0;
	if (ac < 5)
	{
		ft_putstr_fd("usage: ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2", 2);
		exit(1);
	}
	info.count_pipe = ac - 4;
	info.count_cmd = info.count_pipe + 1;
	i = 0;
	if (pipe(info.fd_pipe) == -1)
	{
		ft_putstr_fd("pipe failed", 2);
		exit(1);
	}
	pid = fork();
	printf("pid: %d\n", pid);
	if (pid < 0)
	{
		ft_putstr_fd("fork failed", 2);
		exit(1);
	}
	else if (pid == 0)
	{
		info.fd_infile = open(av[1], O_RDONLY);
		if (info.fd_infile < 0)
		{
			ft_putstr_fd("input file doesn't exist", 2);
			exit(1);
		}
		close(info.fd_pipe[0]); //pipe[0] -> read / pipe[1] -> write
		dup2(info.fd_pipe[1], STDOUT_FILENO); //0 : STDin, 1 : STDout
		close(info.fd_pipe[1]);
		dup2(info.fd_infile, STDIN_FILENO);
		info.cmd_arg = ft_split(av[2], ' ');
		info.path = part_path(env, &info, info.cmd_arg[0]);
		if (execve(info.path, info.cmd_arg, env) == -1)
		{
			ft_putstr_fd("command not found: ", 2);
			ft_putendl_fd(info.cmd_arg[0], 2);
			exit(1);
		}	
	}
	else if (pid > 0)
	{
		waitpid(pid, &info.pid_status, WNOHANG);
		// info.fd_outfile = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
		// if (info.fd_outfile < 0)
		// {
		// 	ft_putstr_fd("output file doesn't exist", 2);
		// 	exit(1);
		// }
		close(info.fd_pipe[1]); //pipe[0] -> read / pipe[1] -> write
		// dup2(info.fd_pipe[0], STDIN_FILENO);
		// close(info.fd_pipe[0]);
		// dup2(info.fd_outfile, STDOUT_FILENO);
		info.cmd_arg = ft_split(av[3], ' ');
		info.path = part_path(env, &info, info.cmd_arg[0]);
		if (ac > 4)
		{
			pid_t pid2;

			if(pipe(info.fd_other_pipe) == -1)
			{
				ft_putstr_fd("pipe failed", 2);
				exit(1);
			}
			pid2 = fork();
						printf("pid2: %d\n", pid2);
			if (pid2 < 0)
			{
				ft_putstr_fd("fork failed", 2);
				exit(1);
			}
			if (pid2 == 0)
			{
				dup2(info.fd_pipe[0], 0);
				dup2(info.fd_other_pipe[1],1);
				close(info.fd_other_pipe[0]);
				/*cmd받아와 실행*/
				if (execve(info.path, info.cmd_arg, env) == -1)
				{
					ft_putstr_fd("command not found: ", 2);
					ft_putendl_fd(info.cmd_arg[0], 2);
					ft_free(&info);
					exit(1);
				}
			}
			else
			{
				waitpid(pid2, &info.pid_status2, WNOHANG);
				info.fd_outfile = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
				if (info.fd_outfile < 0)
					ft_exit_msg("output doesn't exist");
				close(info.fd_pipe[1]); //pipe[0] -> read / pipe[1] -> write
				dup2(info.fd_pipe[0], STDIN_FILENO);
				close(info.fd_pipe[0]);
				dup2(info.fd_outfile, STDOUT_FILENO);
				info.cmd_arg = ft_split(av[3], ' ');
				info.path = part_path(env, &info, info.cmd_arg[0]);
				if (execve(info.path, info.cmd_arg, env) == -1)
				{
					ft_putstr_fd("command not found: ", 2);
					ft_putendl_fd(info.cmd_arg[0], 2);
					ft_free(&info);
					exit(1);
				}
			}
		}
		else
		{
			info.fd_outfile = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
			if (info.fd_outfile < 0)
			{
				ft_putstr_fd("output file doesn't exist", 2);
				exit(1);
			}
			dup2(info.fd_outfile, 1);
			dup2(info.fd_pipe[0], STDIN_FILENO);
			// close(info.fd_pipe[1]);
			close(info.fd_pipe[0]);
			// dup2(info.fd_outfile, STDOUT_FILENO);
			if (execve(info.path, info.cmd_arg, env) == -1)
			{
				ft_putstr_fd("command not found: ", 2);
				ft_putendl_fd(info.cmd_arg[0], 2);
				ft_free(&info);
				exit(1);
			}
		}
	}
	ft_free(&info);
	close(info.fd_outfile);
	close(info.fd_infile);
	return (EXIT_SUCCESS);
}
