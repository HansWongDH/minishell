/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:27:02 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/08 15:03:13 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_cmd(char **s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (parse_symbol(s[i]) > 1)
			i = i + 2;
		else
			return (s[i]);
	}
	return (s[i]);
}

void	set_cmd(t_cmdlist *cmd)
{
	t_cmdlist	*lst;

	lst = cmd;
	while (lst)
	{
		lst->cmd.cmd = ft_strdup(check_cmd(lst->cmd.args));
		lst = lst->next;
	}
}

void	parse_cmd(t_cmdlist *cmd)
{
	if (ft_strcmp(cmd->cmd.cmd, "export")

}

