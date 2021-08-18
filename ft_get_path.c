#include "./includes/pipex.h"

int	get_path(char *str, t_info *info, int flag)
{
	if (!ft_strncmp(str, "/", 1)) // '/'로 패스가 있을때
	{
		if (flag == 1)
			info->path1 = str;
		else
			info->path2 = str;
		return (1);
	}
	return (0);
	// cmd_tmp = ft_split(str, ' '); // ls -al 등을 위해 커맨드 스플릿

}

char	**complete_path(char *cmd_tmp)
{
	char *tmp_path[5];

	tmp_path[0] = ft_strjoin("/usr/local/bin/", cmd_tmp);
	tmp_path[1] = ft_strjoin("/usr/bin/", cmd_tmp);
	tmp_path[2] = ft_strjoin("/bin/", cmd_tmp);
	tmp_path[3] = ft_strjoin("/usr/sbin/", cmd_tmp);
	tmp_path[4] = ft_strjoin("/sbin/", cmd_tmp);

	return (tmp_path);
}