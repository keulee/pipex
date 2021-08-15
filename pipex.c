#include "./includes/pipex.h"

int	main(int ac, char **av, char **en)
{
	// (void)ac;
	(void)en;
	(void)av;
	if (ac != 5)
	{
		ft_exit_msg("Usage: ./pipex file1 cmd1 cmd2 file2");
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