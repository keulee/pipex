#include "includes/pipex_bonus.h"

void	free_tab2(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

void	ft_free(t_info *info)
{
	free(info->path);
	free_tab2(info->cmd_arg);
	info->path = NULL;
	info->cmd_arg = NULL;
}