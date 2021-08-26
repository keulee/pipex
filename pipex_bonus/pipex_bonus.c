#include "includes/pipex_bonus.h"

int	main(int ac, char **av, char **env)
{
	t_info	info;
	int		pid;

	(void) env;
	(void)av;
	if (ac < 4)
	{
		ft_putstr_fd("usage: ./pipex here_doc LIMITER cmd cmd1 file\n", 2);
		ft_putstr_fd("usage: ./pipex file1 cmd1 cmd2 file2", 2);
		exit(1);
	}
	if (pipe(info.fd_pipe) == -1) // if success, fd_pipe[0]는 파이프의 읽기 끝단을 의미하는 파일 디스크립터가 되고, fd_pipe[1]은 파이프의 쓰기 끝단을 의미하는 파일 디스크립터가 된다.
	{
		ft_putstr_fd("pipe failed", 2);
		exit(1);
	}
	pid = fork();
	if (pid < 0)
		ft_putstr_fd("fork failed", 2);
	else if (pid == 0)
	{
		if (ft_strncmp(av[1], "here_doc", 8) == 0)
		{
			printf("heredoc exist\n");
			ft_heredoc(av[2]);
		}
		else
			child_process(&info, av, env);
	}
	else if (pid > 0)
	{
		if (ft_strncmp(av[1], "here_doc", 8) == 0)
		{
			wait(0);
			printf("heredoc config needed\n");
		}
		else
		{
			printf("enter here also?\n");
			parents_process(&info, av, env, &pid);
		}
	}
	// pipex_process(&info, av, env);
	// ft_free(&info);
	// close(info.fd_outfile);
	// close(info.fd_infile);
	return (EXIT_SUCCESS);
}
