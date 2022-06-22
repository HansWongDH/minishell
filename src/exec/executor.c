/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echai <echai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 20:46:04 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/22 15:11:32 by echai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**listto2d(void)
{
	t_list	*lst;
	char	**ret;
	int		i;

	lst = g_env;
	ret = ft_calloc(sizeof(char *), ft_lstsize(lst) + 1);
	i = 0;
	while (lst)
	{
		ret[i] = ft_strdup(lst->content);
		lst = lst->next;
	}
	return (ret);
}

char	*pathextract(char *s, int *i)
{
	char	*ev;
	char	*ret;
	int		start;
	int		len;

	start = *i;
	ev = ft_getenv("PATH");
	while (ev[*i] && ev[*i] != ':')
		(*i)++;
	len = *i - start;
	ret = ft_combine_key(ft_substr(ev, start, len), ft_strdup(s), '/');
	if (ev[*i] == ':')
		(*i)++;
	if (!ev[*i])
		return (NULL);
	return (ret);
}

char	**argumentextract(char *s, t_command cmd)
{
	char	**ret;
	int		i;

	i = 1;
	ret = ft_calloc(sizeof(char *), ft_lstsize(cmd.args) + 2);
	ret[0] = s;
	while (cmd.args)
	{
		ret[i] = *(char **)cmd.args->content;
		cmd.args = cmd.args->next;
		i++;
	}
	return (ret);
}

int	executor(t_command cmd, t_shell *sh)
{
	char	**env;
	char	*exe;
	char	**arg;
	int		i;

	i = 0;
	(void)sh;
	env = listto2d();
	exe = NULL;
	arg = NULL;
	arg = argumentextract(*cmd.cmd, cmd);
	while (execve(exe, arg, env) < 0)
	{
		exe = pathextract(*cmd.cmd, &i);
		if (!exe)
			exit(error_msg(1, 2, *cmd.cmd, ": command not found"));
	}
	exit(0);
}

int	execute(t_command cmd, t_shell *sh)
{
	int	pid;
	int	status;

	pid = fork();
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (pid == 0)
		executor(cmd, sh);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (127);
	return (0);
}
