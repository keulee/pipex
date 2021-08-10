#include "./includes/pipex.h"

int	main(void)
{
	int test=20;
	pid_t pid;

	pid = fork();
	if (pid == 0)
		test++;
	else
	{
		printf("parents process pid : %d\n", pid);
		test--;
	}
	
	if (pid == -1)
		printf("child process create failed\n");
	else if (pid == 0)
		printf("child process : %d\n", test);
	else
	{
		printf("parents process pid : %d\n", pid);
		printf("parents process : %d\n", test);
	}
	
		
	return (EXIT_SUCCESS);
}