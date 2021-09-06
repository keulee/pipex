/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keulee <keulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 20:14:11 by keulee            #+#    #+#             */
/*   Updated: 2021/09/07 00:41:30 by keulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*
** have to managed :
** 1) /pipex user1 "grep hello" "awk \"'{count++} END {print count}'\"" user2 2> user2
** 2) /pipex user1 "grep hello" "awk '\"{count++} END {print count}\"'" user2 2> user2 
** 3) /pipex user1 "grep hello" "awk \"{count++} END {print count}\"" user2 2> user2
** 4) /pipex user1 "grep hello" "awk '{count++} END {print count}'" user2 2> user2
** 5) "awk -F ":" '{ $2 = "" ; print $0 }' /etc/passwd"
** 6) awk 'END {print NR}'
** 7) awk 'length($0)>75 {print}'
*/

size_t count_bunch(char *str)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ')
		{
			if (str[i] == 39)
			{
				i++;
				while (str[i] != 39 && str[i] != '\0')
					i++;
				count++;
			}
			else if (str[i] == 34)
			{
				i++;
				while (str[i] != 34 && str[i] != '\0')
					i++;
				count++;
			}
			else
			{
				while (str[i] != ' ' && str[i] != '\0')
					i++;
				count++;
			}
		}
		if (str[i] == '\0')
			break ;
		else
			i++;
	}
	return (count);
}

int	ft_tab_len(char const *s, char c, int i)
{
	int	len;

	len = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		i++;
		len++;
	}
	return (len);
}

char	**parsing_str(char *str)
{
	char	**res;
	size_t	len;

	(void)res;
	if (str == NULL)
		return (NULL);
	printf("str : %s\n", str);
	len = count_bunch(str);
	printf("len : %d\n", (int)len);
	res = ft_calloc(sizeof(char *), len + 1);
	if (!res)
		return (NULL);
	int i = 0;
	int j = 0;
	int count;
	while (str[i] && j < (int)len)
	{
		count = 0;
		if (str[i] != ' ')
		{
			if (str[i] == 39)
			{
				i++;
				printf("tab len1 : %d\n", ft_tab_len(str, 39, i));
				res[j] = ft_calloc(sizeof(char), ft_tab_len(str, 39, i) + 1);
				if (!res)
					return (NULL);
				while (str[i] != '\0' && str[i] != 39)
					res[j][count++] = str[i++];

			}
			else if (str[i] == 34)
			{
				i++;
				printf("tab len2 : %d\n", ft_tab_len(str, 34, i));
				res[j] = ft_calloc(sizeof(char), ft_tab_len(str, 34, i) + 1);
				if (!res)
					return (NULL);
				while (str[i] != '\0' && str[i] != 34)
					res[j][count++] = str[i++];
			}
			else
			{
				printf("tab len3 : %d\n", ft_tab_len(str, ' ', i));
				res[j] = ft_calloc(sizeof(char), ft_tab_len(str, ' ', i) + 1);
				if (!res)
					return (NULL);
				while (str[i] != '\0' && str[i] != ' ')
					res[j][count++] = str[i++];
			}
			
		}
		i++;
		printf("j : %d\n", j);
		printf("i : %d\n", i);
		printf("count : %d\n", count);
		res[j][count] = '\0';
		j++;
	}
	res[j] = NULL;
	return (res);
}

int	main(int ac, char **av, char **env)
{
	t_info	info;
	// char	*path;

	// (void)env;
	// (void)path;
	// if (ac == 2)
	// {
	// 	// parsing_str(av[1]);
	// 	info.cmd_arg = parsing_str(av[1]);
	// 	int i = 0;
	// 	while (info.cmd_arg[i])
	// 	{
	// 		printf("cmd[%d] : %s\n", i, info.cmd_arg[i]);
	// 		i++;
	// 	}
	// }
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

	// info.cmd_arg = ft_split(av[2], ' ');
	// printf("info.cmd_arg : %s\n", info.cmd_arg[0]);
	// info.path = part_path(env, &info, info.cmd_arg[0]);
	// printf("info.path : %s\n", info.path);
	// int i = 0;
	// while (info.cmd_arg[i] != NULL)
	// 	printf("info.cmd_arg : %s\n", info.cmd_arg[i++]);
	
	pipex_process(&info, av, env);
	ft_free(&info);
	close(info.fd_outfile);
	close(info.fd_infile);
	return (EXIT_SUCCESS);
}

