/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 21:39:02 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/08 17:07:29 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmdlist_expansion(t_cmdlist *list)
{
	t_cmdlist	*temp;

	temp = list;
	while (temp)
	{
		env_treatment(temp->cmd.token);
		quote_treatment(temp->cmd.token);
		temp = temp->next;
	}
}

t_cmdlist	*lexer_init(char *s)
{
	int			i;
	char		**token;
	t_cmdlist	*list;

	i = token_length(s);
	if (i < 0)
		return (NULL);
	token = split_token(s, i);
	if (!token)
		return (NULL);
	list = cmdlist_init(token);
	cmdlist_expansion(list);
	set_cmd(list);
	return (list);
}
