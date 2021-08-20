#include "./includes/pipex.h"

int	main(int ac, char **av, char **env)
{
	t_info	info;
	int		pid;

	if (ac != 5)
		ft_exit_msg("usage: ./pipex file1 cmd1 cmd2 file2");

	if (pipe(info.fd_pipe) == -1) // if success, fd_pipe[0]는 파이프의 읽기 끝단을 의미하는 파일 디스크립터가 되고, fd_pipe[1]은 파이프의 쓰기 끝단을 의미하는 파일 디스크립터가 된다.
		ft_exit_msg("pipe failed");
	
	info.fd_infile = open(av[1], O_RDONLY);
	if (info.fd_infile < 0)
		ft_exit_msg("infile doesn't exist");
	
	info.fd_outfile = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
	
	pid = fork();
	if (pid == -1)
		ft_exit_msg("fork failed");
	else if (pid == 0)
	{
		// printf("child\n");
		close(info.fd_pipe[0]); //pipe[0] -> read / pipe[1] -> write
		dup2(info.fd_pipe[1], STDOUT_FILENO); //0 : STDin, 1 : STDout
		close(info.fd_pipe[1]);
		dup2(info.fd_infile, STDIN_FILENO);
		info.cmd_arg = ft_split(av[2], ' ');
		info.path = part_path(env, &info, info.cmd_arg[0]);
		if (execve(info.path, info.cmd_arg, env) == -1)
		{
			free(info.path);
			free_tab2(info.cmd_arg);
			ft_exit_msg("command not found");
		}
	}
	else if (pid > 0)
	{
		int value;
		value = waitpid(pid, &info.pid_status, 0);
		if (WIFEXITED(info.pid_status) == 0)
			exit(1);
		close(info.fd_pipe[1]); //pipe[0] -> read / pipe[1] -> write
		dup2(info.fd_pipe[0], STDIN_FILENO);
		close(info.fd_pipe[0]);
		dup2(info.fd_outfile, STDOUT_FILENO);
		info.cmd_arg = ft_split(av[3], ' ');
		info.path = part_path(env, &info, info.cmd_arg[0]);
		if (execve(info.path, info.cmd_arg, env) == -1)
		{
			free(info.path);
			free_tab2(info.cmd_arg);
			ft_exit_msg("command not found");
		}
	}
	free(info.path);
	free_tab2(info.cmd_arg);
	close(info.fd_outfile);
	close(info.fd_infile);
	return (EXIT_SUCCESS);
}