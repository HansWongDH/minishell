/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlist_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 13:22:58 by wding-ha          #+#    #+#             */
/*   Updated: 2022/07/04 18:28:02 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmdlist	*ft_newcmd(t_command cmd)
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

char	*add_quote_heredoc(char *s)
{
	char	*ret;
	int		i;

	i = 1;
	ret = ft_calloc(sizeof(char *), ft_strlen(s) + 3);
	ret[0] = '\'';
	while (*s)
	{
		ret[i] = *s;
		i++;
		s++;
	}
	ret[i] = '\'';
	return (ret);
}
