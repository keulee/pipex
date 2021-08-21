#include "includes/pipex.h"

void	ft_init(t_info *info, char **env)
{
	info->pid_status = 0;
	info->pathline = NULL;
	info->env = env;
	info->path = NULL;
	info->cmd_arg = NULL;
}