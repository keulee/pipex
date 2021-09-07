/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keulee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:14:43 by keulee            #+#    #+#             */
/*   Updated: 2021/09/07 15:14:44 by keulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	word_count(const char *str, int *i, int *count)
{
	if (str[*i] == 39)
	{
		(*i)++;
		while (str[*i] != 39 && str[*i] != '\0')
			(*i)++;
		(*count)++;
	}
	else if (str[*i] == 34)
	{
		(*i)++;
		while (str[*i] != 34 && str[*i] != '\0')
			(*i)++;
		(*count)++;
	}
	else
	{
		while (str[*i] != ' ' && str[*i] != '\0')
			(*i)++;
		(*count)++;
	}
}

int	count_bunch(const char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ')
			word_count(str, &i, &count);
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

char	**parsing_malloc_str(char *str, char **res, t_parsing *tab)
{
	tab->i = 0;
	tab->j = 0;
	while (str[tab->i] && tab->j < tab->len)
	{
		tab->count = 0;
		if (str[tab->i] != ' ')
		{
			if (str[tab->i] == 39)
				single_quota(str, res, tab);
			else if (str[tab->i] == 34)
				double_quota(str, res, tab);
			else
				space_case(str, res, tab);
		}
		res[tab->j][tab->count] = '\0';
		tab->i++;
		tab->j++;
	}
	res[tab->j] = NULL;
	return (res);
}

char	**parsing_str(const char *str)
{
	t_parsing	tab;
	char		**res;

	if (str == NULL)
		return (NULL);
	tab.len = count_bunch(str);
	res = ft_calloc(sizeof(char *), tab.len + 1);
	if (!res)
		return (NULL);
	return (parsing_malloc_str((char *)str, res, &tab));
}
