/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:27:02 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/22 15:07:13 by echai            ###   ########.fr       */
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
 * @param sh Shell struct
 * @return int 
 */
int	parse_cmd(t_cmdlist *lst, t_shell *sh)
{
	int		ret;

	sh->dstdin = dup(0);
	sh->dstdout = dup(1);
	if (redir_dup(lst->cmd))
		return (1);
	ret = check_builtin(lst->cmd, sh->ex);
	if (ret < 0)
		ret = execute(lst->cmd, sh);
	dup2(sh->dstdin, 0);
	close(sh->dstdin);
	dup2(sh->dstdout, 1);
	close(sh->dstdout);
	return (ret);
}

int	parse_cmdchild(t_cmdlist *lst, t_shell *sh)
{
	int		ret;

	if (redir_dup(lst->cmd))
		return (1);
	ret = check_builtin(lst->cmd, sh->ex);
	if (ret < 0)
		ret = executor(lst->cmd, sh);
	exit(ret);
}

int	child_create(t_cmdlist *lst, t_shell *sh)
{
	if (sh->i != -1)
	{
		dup2(sh->fd[1], 1);
		close(sh->fd[1]);
		close(sh->fd[0]);
	}
	if (sh->i != 0)
	{
		dup2(sh->dstdin, 0);
		close(sh->dstdin);
		close(sh->fd[0]);
		close(sh->fd[1]);
	}
	exit (parse_cmdchild(lst, sh));
}

int	parse_cmdline(t_cmdlist *lst, t_shell *sh)
{
	int	pid;
	int	status;

	parse_heredoc(lst);
	if (lst && !lst->next)
		return (parse_cmd(lst, sh));
	else
	{
		sh->i = 0;
		while (lst)
		{
			pipe(sh->fd);
			if (!lst->next)
				sh->i = -1;
			pid = fork();
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			if (pid == 0)
				return (child_create(lst, sh));
			sh->i++;
			if (sh->i > 0)
				sh->dstdin = dup(sh->fd[0]);
			close(sh->fd[0]);
			close(sh->fd[1]);
			lst = lst->next;
		}
		waitpid(pid, &status, 0);
	}
	return (0);
}
