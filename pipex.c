#include "./includes/pipex.h"

int	main(int ac, char **av, char **en)
{
	(void)ac;
	(void)en;
	(void)av;
	// int test=20;
	// pid_t pid;

	// pid = fork();
	// if (pid == 0)
	// 	test++;
	// else
	// {
	// 	printf("parents process pid : %d\n", pid);
	// 	test--;
	// }
	
	// if (pid == -1)
	// 	printf("child process create failed\n");
	// else if (pid == 0)
	// 	printf("child process : %d\n", test);
	// else
	// {
	// 	printf("parents process pid : %d\n", pid);
	// 	printf("parents process : %d\n", test);
	// }
	// int fd;
	// int fd2;

	// // if (ac == 1)
	// // 	perror(av[0]);

	// fd = open(av[1], O_RDONLY);
	// if (fd < 0)
	// {
	// 	perror(av[1]);
	// 	return (-1);
	// }
	// dup2(fd, STDIN_FILENO);
	// execve("/bin/cat", 0,0);
	// close(fd);

	// fd2 = open(av[2], O_RDWR | O_CREAT, 0644);
	// if(fd2 < 0)
	// {
	// 	perror(av[2]);
	// 	return (-1);
	// }
	// dup2(fd2, STDOUT_FILENO);
	// close(fd2);
	// printf("stdout test\n");
	// int x;

	// x = fork();
	// if (x == 0)
	// {
	// 	printf("child\n");
	// 	printf("PID: %d\n", getpid());
	// }
	// else
	// {

	// 	printf("parents\n");
	// 	printf("PID: %d\n", getpid());
	// 	printf("x(child PID): %d\n", x);
	// }

	// int i = 1;
	// if (ac > 1)
	// {
	// 	while (av[i])
	// 	{
	// 		printf("av : %s\n", av[i]);
	// 		printf("en : %s\n", en[i]);
	// 		i++;
	// 	}
	// }

	int fd;
	int fd2;

	fd = open(av[1], O_RDONLY);
	fd2 = open(av[2], O_RDWR | O_TRUNC);
	printf("fd: %d\n", fd);
	printf("here\n");

	dup2(fd2, 1);
	printf("works or not?\n");
	// printf("yep\n");
		
	return (EXIT_SUCCESS);
}