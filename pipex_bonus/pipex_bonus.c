#include "includes/pipex_bonus.h"

// void	ft_free(t_info *info)
// {
// 	free(info->path);
// 	free_tab2(info->cmd_arg);
// 	info->path = NULL;
// 	info->cmd_arg = NULL;
// }

int	main(int ac, char **av, char **env)
{
	t_info	info;
	int		i;
	pid_t	pid;

	(void)env;
	(void)av;
	(void)pid;
	i = 0;
	if (ac < 5)
	{
		ft_putstr_fd("usage: ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2", 2);
		exit(1);
	}
	info.count_pipe = ac - 4;
	info.count_cmd = info.count_pipe + 1;
	printf("count pipe : %d\n", info.count_pipe);
	printf("count cmd : %d\n", info.count_cmd);
	/*
	multiple pipe created
	*/
	while (i < info.count_pipe)
	{
		if (pipe(info.fd_pipe + i * 2) == -1)
		{
			ft_putstr_fd("pipe failed", 2);
			exit(1);
		}
		i++;
	}
	/* pipe test
	** printf("pipe print : %d\n", *(info.fd_pipe + 0));
	** printf("pipe print : %d\n", *(info.fd_pipe + 1));
	** printf("pipe print : %d\n", *(info.fd_pipe + 2));
	** printf("pipe print : %d\n", *(info.fd_pipe + 3));
	*/
	while (info.count_cmd)
	{
		pid = fork();
		if (pid < 0)
		{
			ft_putstr_fd("fork failed", 2);
			exit(1);
		}
		else if (pid == 0)
	}

	// pipex_process(&info, av, env);
	// ft_free(&info);
	// close(info.fd_outfile);
	// close(info.fd_infile);
	return (EXIT_SUCCESS);
}
