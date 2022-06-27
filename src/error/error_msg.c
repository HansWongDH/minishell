/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 03:15:11 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/27 20:25:13 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_msg(int i, int fd, char *args, char *s)
{
	ft_putstr_fd(args, fd);
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
	return (i);
}

void	*token_error(char **s)
{
	free2d(s);
	export_exit(258);
	return (NULL);
}
