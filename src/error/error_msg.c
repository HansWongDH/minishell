/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 03:15:11 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/16 16:14:55 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_msg(int i, char *s)
{
	ft_putstr_fd(s, 2);
	return (i);
}

void	*token_error(char **s)
{
	free2d(s);
	return (NULL);
}
