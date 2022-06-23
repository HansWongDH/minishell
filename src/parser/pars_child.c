/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echai <echai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:27:02 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/23 13:20:42 by echai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	fuck_u(t_cmdlist *lst, t_shell *sh)
{
	sh->i++;
	if (sh->i > 0)
		sh->dstdin = dup(sh->fd[0]);
	close(sh->fd[0]);
	close(sh->fd[1]);
	lst = lst->next;
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
			if (pid == 0)
				return (child_create(lst, sh));
			fuck_u(lst, sh);
		}
		waitpid(pid, &status, 0);
	}
	return (0);
}
