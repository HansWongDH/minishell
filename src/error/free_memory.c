/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 11:38:32 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/23 15:23:03 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_linkedlist(t_list	*cmd)
{
	t_list	*lst;
	t_list	*hold;

	lst = cmd;
	while (lst)
	{
		hold = lst->next;
		free(lst);
		lst = hold;
	}
}

void	free_linkedlist2(t_list	*cmd)
{
	t_list	*lst;
	t_list	*hold;

	lst = cmd;
	while (lst)
	{
		hold = lst->next;
		free(lst->content);
		free(lst);
		lst = hold;
	}
}

void	free_cmdlist(t_cmdlist **cmd)
{
	t_cmdlist	*lst;

	if (*cmd)
	{
		lst = (*cmd)->next;
		free2d((*cmd)->cmd.token);
		free_linkedlist((*cmd)->cmd.args);
		free_linkedlist2((*cmd)->cmd.redir);
		free(*cmd);
		*cmd = lst;
	}
}
