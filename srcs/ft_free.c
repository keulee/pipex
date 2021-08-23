#include "../includes/pipex.h"

void	ft_free(t_info *info)
{
	free(info->path);
	free_tab2(info->cmd_arg);
	info->path = NULL;
	info->cmd_arg = NULL;
}