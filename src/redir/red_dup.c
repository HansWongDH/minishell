/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_dup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 17:18:11 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/21 18:32:54 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_routine(int fd, char *s)
{
	char	*str;

	while (1)
	{
		str = readline("> ");
		if (!ft_strcmp(str, s))
			break ;
		ft_putstr_fd((ft_strjoinfree(str, ft_strdup("\n"))), fd);
	}
	exit(0);
}

int	ft_heredoc(char *s)
{
	int		fd;
	int		pid;
	int		status;

	pid = fork();
	fd = open("temp", O_CREAT | O_TRUNC | O_WRONLY, 0700);
	if (pid == 0)
		heredoc_routine(fd, s);
	waitpid(pid, &status, 0);
	close(fd);
	fd = open("temp", O_RDONLY, 0700);
	unlink("temp");
	return (fd);
}

int	redir_fd(t_command cmd, int *in, int *out)
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
			*in = ft_heredoc(*red->file);
		lst = lst->next;
	}
	if (error)
		return (error_msg(1, 2, *red->file, "No such file and directory\n"));
	return (0);
}

int	redir_dup(t_command cmd)
{
	int	out;
	int	in;

	in = 0;
	out = 0;
	if (redir_fd(cmd, &in, &out))
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
