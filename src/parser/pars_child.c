/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:27:02 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/25 03:13:55 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_cmdchild(t_cmdlist *lst, t_shell *sh)
{
	int		ret;

	if (redir_dup(lst->cmd))
		return (1);
	if (lst->cmd.cmd)
	{
		ret = check_builtin(lst->cmd, sh->ex);
		if (ret < 0)
			ret = executor(lst->cmd, sh);
	}
	return (ret);
}

void	killchild(int signo)
{
	(void)signo;
	kill(0, SIGINT);
}

int	child_create(t_cmdlist *lst, t_shell *sh)
{
	signal(SIGINT, killchild);
	signal(SIGQUIT, SIG_DFL);
	if (sh->i != -1)
		dup2(sh->fd[1], 1);
	if (sh->i != 0)
	{
		dup2(sh->readend, 0);
		close(sh->readend);
	}
	close(sh->fd[0]);
	close(sh->fd[1]);
	exit (parse_cmdchild(lst, sh));
}

int	fork_it(t_cmdlist *lst, t_shell *sh)
{
	int			pid;
	int			status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	sh->i = 0;
	while (lst)
	{
		pipe(sh->fd);
		if (!lst->next)
			sh->i = -1;
		pid = fork();
		if (pid == 0)
			child_create(lst, sh);
		sh->i++;
		if (sh->i > 0)
			sh->readend = dup(sh->fd[0]);
		close(sh->fd[0]);
		close(sh->fd[1]);
		free_cmdlist(&lst);
	}
	while (waitpid(-1, &status, 0) > 0)
		;
	if (WIFEXITED(status))
		return (127);
	return (0);
}

int	parse_cmdline(t_cmdlist *lst, t_shell *sh)
{
	parse_heredoc(lst);
	if (lst && !lst->next)
		return (parse_cmd(lst, sh));
	else
		return (fork_it(lst, sh));
	return (0);
}
