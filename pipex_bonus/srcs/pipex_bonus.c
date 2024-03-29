/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keulee <keulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 20:19:17 by keulee            #+#    #+#             */
/*   Updated: 2021/09/07 17:45:40 by keulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	heredoc_cmd_check(int ac, char **av, t_info *info)
{
	if (ac == 6)
	{
		if (ft_strcmp(av[1], "here_doc") != 0)
		{
			ft_putendl_fd("command here_doc not corrected", 2);
			exit(1);
		}
		else
			info->h_flag = 1;
	}
}

int	main(int ac, char **av, char **env)
{
	t_info	info;

	if (ac < 5 || ac > 6)
	{
		ft_putendl_fd("usage1: ./pipex here_doc LIMITER cmd cmd1 file", 2);
		ft_putendl_fd("usage2: ./pipex file1 cmd1 cmd2 file2", 2);
		exit(1);
	}
	info.h_flag = 0;
	heredoc_cmd_check(ac, av, &info);
	if (pipe(info.fd_pipe) == -1)
	{
		ft_putendl_fd("pipe failed", 2);
		exit(1);
	}
	pipex_with_heredoc(&info, av, env);
	ft_free(&info);
	close(info.fd_infile);
	close(info.fd_outfile);
	return (EXIT_SUCCESS);
}
