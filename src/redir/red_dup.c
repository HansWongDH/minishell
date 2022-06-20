/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_dup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echai <echai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 17:18:11 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/20 11:57:34 by echai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Redirection fd function
 * 
 * @param cmd cmd struct
 * @return int output fd 
 */
int	redir_fd(t_command cmd)
{
	t_list	*lst;
	t_redir	*red;
	int		fd;
	int		out;

	lst = cmd.redir;
	while (lst)
	{
		red = lst->content;
		if (red->red < 4)
			fd = open(*red->file, O_WRONLY | O_TRUNC | O_CREAT, 0700);
		lst = lst->next;
	}
	out = dup(1);
	dup2(fd, 1);
	close(fd);
	return (out);
}
