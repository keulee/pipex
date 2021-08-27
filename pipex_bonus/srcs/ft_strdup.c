#include "../includes/pipex_bonus.h"

char	*ft_strdup(const char *src)
{
	char	*copy;
	int		i;
	int		len;

	i = 0;
	copy = NULL;
	len = ft_strlen(src);
	copy = (char *)ft_calloc((len + 1), sizeof(char));
	if (!copy)
		return (NULL);
	while (i < len)
	{
		copy[i] = src[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
