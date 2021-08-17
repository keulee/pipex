#include "./includes/pipex.h"

int	get_path(char *str)
{
	if (!strncmp(str, "/", 1)) // '/'로 패스가 있을때
		return (1);
	return (0);
	// cmd_tmp = ft_split(str, ' '); // ls -al 등을 위해 커맨드 스플릿
}

char	*complete_path(char *cmd)
{
	char 	**cmd_tmp;
	char	*path_tmp[5];
	int		i;		

	cmd_tmp = ft_split(cmd, ' ');
	if (get_path(cmd_tmp[0]) == 1)
		return (cmd_tmp[0]);
	path_tmp[0] = ft_strjoin("/usr/local/bin/", cmd_tmp[0]);
	path_tmp[1] = ft_strjoin("/usr/bin/", cmd_tmp[0]);
	path_tmp[2] = ft_strjoin("/bin/", cmd_tmp[0]);
	path_tmp[3] = ft_strjoin("/usr/sbin/", cmd_tmp[0]);
	path_tmp[4] = ft_strjoin("/sbin/", cmd_tmp[0]);

	i = 0;
	while (i < 5)
	{
		if (access(path_tmp[i], F_OK | X_OK) == 0)
			return (path_tmp[i]);
		i++;
	}
	return (NULL);
}

int	main(int ac, char **av, char **env)
{
	t_info	info;
	int		pid;
	char	*cmd1;
	char	*cmd2;

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
	(void)env;
	(void)info;
	(void)pid;
	// char *str1[2];
	// str1[0] = "/bin/cat";
	// str1[1] = NULL;

	// char *str2[2];
	// str2[0] = "/bin/ls -al";
	// str2[1] = NULL;

	cmd1 = av[2]; //raw command1
	cmd2 = av[3]; //raw command2
	printf("cmd1 : %s\n", cmd1);
	printf("cmd2 : %s\n", cmd2);

	// char *test = NULL;
	// char *test2 = NULL;

	// if (complete_path(cmd1, &info, 1) == 1)
	// 	test = info.path1;
	// if (complete_path(cmd2, &info, 2) == 1)
	// 	test2 = info.path2;
	// test2 = complete_path(cmd2);

	if (ac != 5)
		ft_exit_msg("Usage: ./pipex file1 cmd1 cmd2 file2");
	// int i = 0;
	// // while (i < 5)
	// 	printf("path : %s\n", test);
	// 	printf("path : %s\n", test2);
	// i = 0;
	// while (i < 5)
		// printf("path : %s\n", test2[i++]);

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
		info.cmd_arg1 = ft_split(av[2], ' ');
		info.path1 = complete_path(av[2]);
		if (!info.path1)
			perror(info.path1);
		if (execve(info.path1, info.cmd_arg1, env) == -1)
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
		info.cmd_arg2 = ft_split(av[3], ' ');
		info.path2 = complete_path(av[3]);
		if (!info.path2)
			ft_exit_msg("no such path");
		if (execve(info.path2, info.cmd_arg2, env) == -1)
		{
			ft_exit_msg("cmd not found");
		}
	}
	return (EXIT_SUCCESS);
}