/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keulee <keulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 20:14:11 by keulee            #+#    #+#             */
/*   Updated: 2021/09/06 17:13:56 by keulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*
** have to managed :
** 1) /pipex user1 "grep hello" "awk \"'{count++} END {print count}'\"" user2 2> user2
** 2) /pipex user1 "grep hello" "awk '\"{count++} END {print count}\"'" user2 2> user2 
** 3) /pipex user1 "grep hello" "awk \"{count++} END {print count}\"" user2 2> user2
** 4) /pipex user1 "grep hello" "awk '{count++} END {print count}'" user2 2> user2
*/

int	main(int ac, char **av, char **env)
{
	t_info	info;
	// char	*path;

	// (void)env;
	// (void)path;
	if (ac != 5)
	{
		ft_putendl_fd("usage: ./pipex file1 cmd1 cmd2 file2", 2);
		exit(1);
	}
	if (pipe(info.fd_pipe) == -1) // if success, fd_pipe[0]는 파이프의 읽기 끝단을 의미하는 파일 디스크립터가 되고, fd_pipe[1]은 파이프의 쓰기 끝단을 의미하는 파일 디스크립터가 된다.
	{
		ft_putendl_fd("pipe failed", 2);
		exit(1);
	}
	info.cmd_arg = ft_split(av[2], ' ');
	printf("info.cmd_arg : %s\n", info.cmd_arg[0]);
	info.path = part_path(env, &info, info.cmd_arg[0]);
	printf("info.path : %s\n", info.path);
	int i = 0;
	while (info.cmd_arg[i] != NULL)
		printf("info.cmd_arg : %s\n", info.cmd_arg[i++]);
	
	// pipex_process(&info, av, env);
	ft_free(&info);
	close(info.fd_outfile);
	close(info.fd_infile);
	return (EXIT_SUCCESS);
}
