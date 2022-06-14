/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 21:39:02 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/14 19:31:26 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_tolower(t_cmdlist *lst)
{
	char	*s;
	int		i;

	i = 0;
	s = *lst->cmd.cmd;
	while (s[i])
	{
		s[i] = ft_tolower(s[i]);
		i++;
	}
}

void	cmdlist_expansion(t_cmdlist *list, int ex)
{
	t_cmdlist	*temp;

	temp = list;
	while (temp)
	{
		env_treatment(temp->cmd.token, ex);
		quote_treatment(temp->cmd.token, ex);
		temp = temp->next;
	}
}

t_cmdlist	*lexer_init(char *s, int ex)
{
	int			i;
	char		**token;
	t_cmdlist	*lst;

	i = token_length(s);
	if (i <= 0)
		return (NULL);
	token = split_token(s, i);
	lst = cmdlist_init(token);
	set_cmd(lst);
	cmdlist_expansion(lst, ex);
	cmd_tolower(lst);
	return (lst);
}
