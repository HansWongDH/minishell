/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_dup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echai <echai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 17:18:11 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/22 15:05:58 by echai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*tempfile_gen(t_shell *sh)
{
	char	*s;
	char	*ret;

	s = ft_itoa(sh->i);
	ret = ft_strjoin("temp", s);
	free(s);
	return (ret);
}

int	heredoc_routine(char *s)
{
	char	*str;
	int		fd;

	fd = open("temp", O_CREAT | O_TRUNC | O_WRONLY, 0700);
	while (1)
	{
		str = readline("> ");
		if (!ft_strcmp(str, s))
			break ;
		ft_putstr_fd((ft_strjoinfree(str, ft_strdup("\n"))), fd);
	}
	close(fd);
	exit(0);
}

int	ft_heredoc(char *s, t_shell *sh)
{
	int		fd;
	int		pid;
	int		status;
	char	*file;

	file = tempfile_gen(sh);
	pid = fork();
	signal(SIGINT, SIG_DFL);
	if (pid == 0)
		heredoc_routine(s);
	waitpid(pid, &status, 0);
	fd = open("temp", O_RDONLY, 0700);
	unlink("temp");
	return (fd);
}

int	redir_fd(t_command cmd, int *in, int *out, t_shell *sh)
{
	t_list	*lst;
	t_redir	*red;
	char	*error;

	lst = cmd.redir;
	error = NULL;
	while (lst)
	{
		red = lst->content;
		if (red->red == OUTFILE)
			*out = open(*red->file, O_WRONLY | O_TRUNC | O_CREAT, 0700);
		if (red->red == DOUTFILE)
			*out = open(*red->file, O_WRONLY | O_APPEND | O_CREAT, 0700);
		if (red->red == INFILE)
		{
			*in = open(*red->file, O_RDONLY, 0700);
			if (*in < 0 && !error)
				error = *red->file;
		}
		if (red->red == HEREDOC)
			*in = ft_heredoc(*red->file, sh);
		lst = lst->next;
	}
	if (error)
		return (error_msg(1, 2, *red->file, "No such file and directory\n"));
	return (0);
}

int	redir_dup(t_command cmd, t_shell *sh)
{
	int	out;
	int	in;

	in = 0;
	out = 0;
	if (redir_fd(cmd, &in, &out, sh))
		return (1);
	if (in > 0)
	{
		dup2(in, 0);
		close(in);
	}
	if (out > 0)
	{
		dup2(out, 1);
		close(out);
	}
	return (0);
}
