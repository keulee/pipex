#include "includes/pipex_bonus.h"

void	insert_node(t_node **node, char *cmd)
{
	t_node	*new;
	t_node	*tmp;

	new = (t_node *)malloc(sizeof(t_node));
	if (!new)
		ft_exit_msg("ERROR");
	tmp = *node;
	new->next = NULL;
	new->cmd = cmd;
	if (tmp == NULL)
	{
		*node = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}