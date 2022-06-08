/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlist_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 13:22:58 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/08 13:35:22 by wding-ha         ###   ########.fr       */
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

int	parse_symbol(char *s)
{
	if (!ft_strcmp(s, ">"))
		return (OUTFILE);
	if (!ft_strcmp(s, ">>"))
		return (DOUTFILE);
	if (!ft_strcmp(s, "<"))
		return (INFILE);
	if (!ft_strcmp(s, "<<"))
		return (HEREDOC);
	if (!ft_strcmp(s, "|"))
		return (PIPE);
	return (0);
}
