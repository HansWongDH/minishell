/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_dup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 17:18:11 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/20 21:35:40 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_fd(t_command cmd, int *in, int *out)
{
	t_list	*lst;
	t_redir	*red;

	lst = cmd.redir;
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
			if (*in < 0)
				return (error_msg(1, "No such file and directory\n"));
		}
		if (red->red == HEREDOC)
			*in = open(*red->file, O_WRONLY | O_APPEND | O_CREAT, 0700);
		lst = lst->next;
	}
	return (1);
}

int	redir_dup(t_command cmd)
{
	int	out;
	int	in;

	in = 0;
	out = 0;
	redir_fd(cmd, &in, &out);
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