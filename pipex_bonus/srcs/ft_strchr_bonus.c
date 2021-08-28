#include "../includes/pipex_bonus.h"

int	ft_strchr(const char *s, int c)
{
	char	*ptr;
	char	needle;
	int		i;

	needle = c;
	ptr = (char *)s;
	i = 0;
	while (ptr[i] != '\0')
	{
		if (ptr[i] == c)
			return (1);
		i++;
	}
	if (ptr[i] == c)
		return (1);
	return (0);
}
