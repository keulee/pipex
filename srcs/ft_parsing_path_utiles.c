#include "../includes/pipex.h"

void	single_quota(char *str, char **res, t_parsing *tab)
{
	tab->i++;
	res[tab->j] = ft_calloc(sizeof(char), ft_tab_len(str, 39, tab->i) + 1);
	if (!res)
		return ;
	while (str[tab->i] != '\0' && str[tab->i] != 39)
		res[tab->j][tab->count++] = str[tab->i++];
}

void	double_quota(char *str, char **res, t_parsing *tab)
{
	tab->i++;
	res[tab->j] = ft_calloc(sizeof(char), ft_tab_len(str, 34, tab->i) + 1);
	if (!res)
		return ;
	while (str[tab->i] != '\0' && str[tab->i] != 34)
		res[tab->j][tab->count++] = str[tab->i++];
}

void	space_case(char *str, char **res, t_parsing *tab)
{
	res[tab->j] = ft_calloc(sizeof(char), ft_tab_len(str, ' ', tab->i) + 1);
	if (!res)
		return ;
	while (str[tab->i] != '\0' && str[tab->i] != ' ')
		res[tab->j][tab->count++] = str[tab->i++];
}
