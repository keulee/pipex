/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keulee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 20:10:13 by keulee            #+#    #+#             */
/*   Updated: 2021/09/02 20:10:15 by keulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_free(t_info *info)
{
	free(info->path);
	free_tab2(info->cmd_arg);
	info->path = NULL;
	info->cmd_arg = NULL;
}
