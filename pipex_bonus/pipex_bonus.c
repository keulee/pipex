#include "includes/pipex_bonus.h"

int	main(int ac, char **av, char **env)
{
	t_info	info;

	if (ac < 6)
	{
		ft_putstr_fd("usage: ./pipex here_doc LIMITER cmd cmd1 file", 2);
		exit(1);
	}
	if (pipe(info.fd_pipe) == -1) // if success, fd_pipe[0]는 파이프의 읽기 끝단을 의미하는 파일 디스크립터가 되고, fd_pipe[1]은 파이프의 쓰기 끝단을 의미하는 파일 디스크립터가 된다.
	{
		ft_putstr_fd("pipe failed", 2);
		exit(1);
	}
	pipex_process(&info, av, env);
	ft_free(&info);
	close(info.fd_outfile);
	close(info.fd_infile);
	return (EXIT_SUCCESS);
}
