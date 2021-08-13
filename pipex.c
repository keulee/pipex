#include "./includes/pipex.h"

int	main(int ac, char **av, char **en)
{
	(void)ac;
	(void)en;
	(void)av;
	int fd[2];
	int	pid;
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (pid == 0)
	{
		close(fd[1]);
	}
		
	return (EXIT_SUCCESS);
}