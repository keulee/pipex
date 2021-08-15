#include "./includes/pipex.h"

int	main(int ac, char **av, char **en)
{
	t_info	info;
	int		pid;
	// (void)ac;
	(void)en;
	(void)av;
	if (ac != 5)
		ft_exit_msg("Usage: ./pipex file1 cmd1 cmd2 file2");
	if (pipe(info.fd_pipe) == -1) // if success, fd_pipe[0]는 파이프의 읽기 끝단을 의미하는 파일 디스크립터가 되고, fd_pipe[1]은 파이프의 쓰기 끝단을 의미하는 파일 디스크립터가 된다.
		ft_exit_msg("pipe failed");
	info.fd_infile = open(av[1], O_RDONLY);
	if (info.fd_infile < 0)
		ft_exit_msg("infile doesn't exist");
	info.fd_outfile = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 777);
	pid = fork();
	if (pid == -1)
		ft_exit_msg("fork error");
	if (pid == 0)
	{
		printf("child\n");
		close(info.fd_pipe[0]); //pipe[0] -> read / pipe[1] -> write
		dup2(info.fd_pipe[1], STDOUT_FILENO); //0 : STDin, 1 : STDout
		close(info.fd_pipe[1]);
		dup2(info.fd_infile, STDIN_FILENO);
	}
	else if (pid > 0)
	{
		// wait(0);
		printf("parents\n");
		close(info.fd_pipe[1]); //pipe[0] -> read / pipe[1] -> write
		dup2(info.fd_pipe[0], STDIN_FILENO);
		close(info.fd_pipe[0]);
		dup2(info.fd_outfile, STDOUT_FILENO);
	}
	

	// int fd[2];
	// int	pid;
	// if (pipe(fd) == -1)
	// {
	// 	perror("pipe");
	// 	exit(1);
	// }
	// pid = fork();
	// if (pid == -1)
	// {
	// 	perror("fork");
	// 	exit(1);
	// }
	// else if (pid == 0)
	// {
	// 	close(fd[1]); //쓰기 파이프를 닫아 읽기용으로 사용 (출력부분 필요없음)
	// 	if (fd[0] != 0) //표준 입력이 아니면
	// 	{
	// 		dup2(fd[0], 0); //표준 입력으로 복사
	// 		close(fd[0]);
	// 	}
	// 	execlp("cat", "cat", av[4], (char *)NULL);
	// 	exit(1);
	// }
	// else
	// {
	// 	close(fd[0]); //파이프 입력부분 필요없음
	// 	//파이프의 출력 부분을 표준 출력으로 복사한다. 따라서 부모 프로세스에서 무언가를 출력하면,
	// 	//파이프를 통해 출력된다.
	// 	if (fd[1] != 1)
	// 	{
	// 		dup2(fd[1], 1);
	// 		close(fd[1]);
	// 	}
	// 	execlp(av[1], av[1], "wc", (char *)NULL);
	// 	// wait(pid);
	// 	exit(0);
	// }
	

		
	return (EXIT_SUCCESS);
}