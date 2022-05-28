/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_cmdlist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 13:22:58 by wding-ha          #+#    #+#             */
/*   Updated: 2022/05/28 15:30:06 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_cmdlist	*ft_newcmd(t_commands cmd)
{
	t_cmdlist	*list;

	list = malloc(sizeof(t_cmdlist));
	if (!list)
		return (NULL);
	list->cmd = cmd;
	list->next = NULL;
	return (list);
}

t_cmdlist	*ft_cmdlast(t_cmdlist *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_cmdadd_back(t_cmdlist **lst, t_cmdlist *new)
{
	t_cmdlist	*next;

	if (lst && new)
	{
		if (*lst)
		{
			next = ft_cmdlast(*lst);
			next->next = new;
		}
		else
			*lst = new;
	}
}

void	free2d(char **s)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			free(s[i]);
			i++;
		}
		free(s[i]);
		free(s);
	}
}

t_cmdlist	*cmdlist_init(char **s)
{
	int			i;
	t_commands	cmd;
	t_cmdlist	*list;

	i = 0;
	list = NULL;
	while (s[i])
	{
		cmd = command_table_init(s, &i);
		ft_cmdadd_back(&list, ft_newcmd(cmd));
		if (parse_symbol(s[i]) == PIPE)
			i++;
	}
	free2d(s);
	return (list);
}