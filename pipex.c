#include "./includes/pipex.h"

int	main(int ac, char **av, char **env)
{
	t_info	info;
	int		pid;
	char	*path1;
	char	*path2;

	/* 
	** command lines
	** /usr/local/bin/
	** /usr/bin/
	** /bin/
	** /usr/sbin/
	** /sbin/
	*/
	/*
	** 패스 만들기 위한 과정
	** 1. cmd recuperer => av[2],av[3]
	** 1-1. cmd가 path랑 함께인지 아닌지 확인 (/)
	** 2. ' '로 split해서 옵션 없이 커맨드만 챙기기
	** 3. command lines이랑 strjoin해주기
	** 4. access로 F_OK(존재 유무), X_OK(실행가능 유무)확인 하기
	** 5. 있으면 path리턴, 없으면 오류 (path not found)리턴
	*/

	char *str1[2];
	str1[0] = "/bin/cat";
	str1[1] = NULL;

	char *str2[2];
	str2[0] = "/bin/ls -al";
	str2[1] = NULL;

	path1 = av[2];
	path2 = av[3];
	printf("path1 : %s\n", path1);
	printf("path2 : %s\n", path2);

	if (ac != 5)
		ft_exit_msg("Usage: ./pipex file1 cmd1 cmd2 file2");

	if (pipe(info.fd_pipe) == -1) // if success, fd_pipe[0]는 파이프의 읽기 끝단을 의미하는 파일 디스크립터가 되고, fd_pipe[1]은 파이프의 쓰기 끝단을 의미하는 파일 디스크립터가 된다.
		ft_exit_msg("pipe failed");
	
	info.fd_infile = open(av[1], O_RDONLY);
	if (info.fd_infile < 0)
		ft_exit_msg("infile doesn't exist");
	
	info.fd_outfile = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
	
	pid = fork();
	if (pid == -1)
		ft_exit_msg("fork error");
	else if (pid == 0)
	{
		printf("child\n");
		close(info.fd_pipe[0]); //pipe[0] -> read / pipe[1] -> write
		dup2(info.fd_pipe[1], STDOUT_FILENO); //0 : STDin, 1 : STDout
		close(info.fd_pipe[1]);
		dup2(info.fd_infile, STDIN_FILENO);
		info.cmd1 = ft_split(av[2], ' ');
		if (execve("/bin/cat", info.cmd1, env) == -1)
		{
			ft_exit_msg("cmd not found");
		}
	}
	else if (pid > 0)
	{
		int value;
		value = waitpid(pid, &info.pid_status, 0);
		if (WIFEXITED(info.pid_status) == 0)
			exit(1);
		printf("pid status : %d\n", info.pid_status);
		printf("waitpid : %d\n", value);
		printf("parents\n");
		close(info.fd_pipe[1]); //pipe[0] -> read / pipe[1] -> write
		dup2(info.fd_pipe[0], STDIN_FILENO);
		close(info.fd_pipe[0]);
		dup2(info.fd_outfile, STDOUT_FILENO);
		info.cmd2 = ft_split(av[3], ' ');
		if (execve("/bin/ls", info.cmd2, env) == -1)
		{
			ft_exit_msg("cmd not found");
		}
	}
	return (EXIT_SUCCESS);
}