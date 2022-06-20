/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echai <echai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:27:02 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/20 13:21:24 by echai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 
 * 
 * @param file 
 * @param red 
 * @return t_redir* 
 */
t_redir	*new_redir(char	**file, int red)
{
	t_redir	*lst;

	lst = malloc(sizeof(t_redir));
	lst->file = file;
	lst->red = red;
	return (lst);
}

/**
 * @brief 
 * 
 * @param cmd 
 */
void	check_cmd(t_command *cmd)
{
	int		i;
	t_redir	*red;

	i = 0;
	while (cmd->token[i])
	{
		if (parse_symbol(cmd->token[i]) > 1)
		{
			red = new_redir(&(cmd->token[i + 1]), parse_symbol(cmd->token[i]));
			ft_lstadd_back(&(cmd->redir), ft_lstnew(red));
			i = i + 2;
		}
		else
		{
			if (!cmd->cmd && cmd->token[i])
				cmd->cmd = &(cmd->token[i]);
			else
				ft_lstadd_back(&(cmd->args), ft_lstnew(&(cmd->token[i])));
			i++;
		}
	}
}

/**
 * @brief Set the cmd object
 * 
 * @param cmd Command list
 */
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

/**
 * @brief Checks if one of the commands is a builtin
 * 
 * @param cmd Command
 * @param ex Exit status
 * @return int 
 */
int	check_builtin(t_command cmd, int ex)
{
	char	*s;

	s = *cmd.cmd;
	if (!ft_strcmp(s, "echo"))
		return (bin_echo(cmd));
	if (!ft_strcmp(s, "cd"))
		return (bin_cd(cmd));
	if (!ft_strcmp(s, "pwd"))
		return (bin_pwd(cmd));
	if (!ft_strcmp(s, "export"))
		return (bin_export(cmd));
	if (!ft_strcmp(s, "unset"))
		return (bin_unset(cmd));
	if (!ft_strcmp(s, "env"))
		return (bin_env(cmd));
	if (!ft_strcmp(s, "exit"))
		return (bin_exit(cmd, ex));
	return (-1);
}

/**
 * @brief Parse the command list and delegates command check to builtin
 * 
 * @param lst Command list
 * @param ex Exit status
 * @return int 
 */
int	parse_cmd(t_cmdlist *lst, int ex)
{
	int		ret;

	ret = check_builtin(lst->cmd, ex);
	return (ret);
}
