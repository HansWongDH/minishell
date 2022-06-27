/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_dup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 17:18:11 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/27 16:23:42 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redirection(t_command cmd, t_redir *red, int *in, int *out)
{
	if (red->red == OUTFILE)
	{
		if (*out)
			close(*out);
		*out = open(*red->file, O_WRONLY | O_TRUNC | O_CREAT, 0700);
	}
	if (red->red == DOUTFILE)
	{
		if (*out)
			close(*out);
		*out = open(*red->file, O_WRONLY | O_APPEND | O_CREAT, 0700);
	}
	if (red->red == INFILE)
	{
		if (*in)
			close(*in);
		*in = open(*red->file, O_RDONLY, 0700);
		if (*in < 0)
			return (error_msg(1, 2, *red->file,
					": No such file and directory"));
	}
	if (red->red == HEREDOC)
		*in = cmd.fd;
	return (0);
}

int	redir_fd(t_command cmd, int *in, int *out)
{
	t_list	*lst;

	lst = cmd.redir;
	while (lst)
	{
		if (ft_redirection(cmd, lst->content, in, out))
			return (1);
		lst = lst->next;
	}
	return (0);
}

int	redir_dup(t_command cmd)
{
	int	out;
	int	in;

	in = 0;
	out = 0;
	if (redir_fd(cmd, &in, &out))
	{
		close(cmd.fd);
		return (1);
	}
	else
	{
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
	}
	return (0);
}
