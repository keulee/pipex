#include "../includes/pipex_bonus.h"

void	heredoc_cmd_check(int ac, char **av)
{
	if (ac == 6)
	{
		if (ft_strcmp(av[1], "here_doc") != 0)
		{
			ft_putstr_fd("command here_doc not corrected\n", 2);
			exit(1);
		}
	}
}

int	main(int ac, char **av, char **env)
{
	t_info	info;

	if (ac < 4 || ac > 6)
	{
		ft_putstr_fd("usage: ./pipex here_doc LIMITER cmd cmd1 file\n", 2);
		ft_putstr_fd("usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
		exit(1);
	}
	heredoc_cmd_check(ac, av);
	if (pipe(info.fd_pipe) == -1)
	{
		ft_putstr_fd("pipe failed", 2);
		exit(1);
	}
	pipex_with_heredoc(&info, av, env);
	ft_free(&info);
	close(info.fd_infile);
	close(info.fd_outfile);
	return (EXIT_SUCCESS);
}
