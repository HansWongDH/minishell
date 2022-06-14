/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 11:38:32 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/14 19:26:24 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmdlist(t_cmdlist *cmd)
{
	t_cmdlist	*lst;

	lst = cmd;
	while (lst)
	{
		free2d(lst->cmd.token);
		lst = lst->next;
	}
}
