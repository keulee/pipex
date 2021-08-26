#include "includes/pipex_bonus.h"

void	ft_heredoc(char *limiter)
{
	int		pipe_heredoc[2];
	char	*line;

	(void)limiter;
	if (pipe(pipe_heredoc) == -1)
	{
		ft_putstr_fd("pipe failed", 2);
		exit(1);
	}
	write(1, "pipe heredoc>", 13);
	while (get_next_line(0, &line) > 0)
	{
		if (strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			break ;
		}
	}
	// if (strncmp(limiter, "done", ft_strlen(limiter)) == 0)

}
