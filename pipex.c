#include "./includes/pipex.h"

int	main(void)
{
	int test;

	test = unlink("test.txt");
	printf("unlink test: %d\n", test);
	// test = access("here.txt", F_OK);
	// printf("F_OK (exist): %d\n", test);

	return (EXIT_SUCCESS);
}