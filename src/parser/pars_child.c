/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:27:02 by wding-ha          #+#    #+#             */
/*   Updated: 2022/07/06 17:56:51 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_cmdchild(t_cmdlist *lst, t_shell *sh)
{
	int		ret;

	ret = 0;
	if (redir_dup(lst->cmd))
		return (1);
	if (lst->cmd.cmd)
	{
		ret = check_builtin(lst->cmd);
		if (ret < 0)
			ret = executor(lst->cmd, sh);
	}
	return (ret);
}

int	child_create(t_cmdlist *lst, t_shell *sh)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (sh->i != -1)
		dup2(sh->fd[1], 1);
	if (sh->i != 0)
		dup2(sh->fd[0], 0);
	close(sh->prevfd);
	close(sh->fd[0]);
	close(sh->fd[1]);
	exit (parse_cmdchild(lst, sh));
}

void	dup_and_close(t_shell *sh)
{
	sh->pipe = dup(sh->prevfd);
	close(sh->prevfd);
	close(sh->fd[0]);
	close(sh->fd[1]);
}

int	fork_it(t_cmdlist *lst, t_shell *sh)
{
	int	pid;

	sh->i = 0;
	while (lst)
	{
		pipe(sh->fd);
		sh->prevfd = dup(sh->fd[0]);
		if (sh->i > 0)
		{
			dup2(sh->pipe, sh->fd[0]);
			close(sh->pipe);
		}
		if (!lst->next)
			sh->i = -1;
		pid = fork();
		if (pid == 0)
			child_create(lst, sh);
		sh->i++;
		dup_and_close(sh);
		free_cmdlist(&lst);
	}
	close(sh->pipe);
	return (pid);
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
		pid = fork_it(lst, sh);
		status = waitforchild(pid);
		waitforchild(-1);
		return (status);
	}
}
