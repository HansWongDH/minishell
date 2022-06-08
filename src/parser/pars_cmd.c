/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:27:02 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/08 19:34:02 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_cmd(t_commands *cmd)
{
	int		i;

	i = 0;
	while (cmd->token[i])
	{
		if (parse_symbol(cmd->token[i]) > 1)
			i = i + 2;
		else
		{
			if (!cmd->cmd)
				cmd->cmd = ft_strdup(cmd->token[i]);
			else
				ft_lstadd_back(&(cmd->args), ft_lstnew(cmd->token[i]));
			i++;
		}
	}
}

void	set_cmd(t_cmdlist *cmd)
{
	t_cmdlist	*lst;

	lst = cmd;
	while (lst)
	{
		check_cmd(&(lst->cmd));
		lst = lst->next;
	}
}

int	check_builtin(t_commands cmd)
{
	char	*s;

	s = cmd.cmd;
	if (!ft_strcmp(s, "echo"))
		return (bin_echo(cmd));
	if (!ft_strcmp(s, "cd"))
		return (1);
	if (!ft_strcmp(s, "pwd"))
		return (1);
	if (!ft_strcmp(s, "export"))
		return (bin_export(cmd));
	if (!ft_strcmp(s, "unset"))
		return (1);
	if (!ft_strcmp(s, "env"))
		return (bin_env(cmd));
	if (!ft_strcmp(s, "exit"))
		return (1);
	return (0);
}

void	parse_cmd(t_cmdlist *lst)
{
	if (!check_builtin(lst->cmd))
		return ;
}

