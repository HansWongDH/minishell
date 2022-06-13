/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:59:42 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/13 16:28:44 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bin_pwd(t_command cmd)
{
	char	*s;
	char	buf[200];

	if (cmd.args)
		return (error_msg(1, "pwd: too many arguments\n"));
	s = getcwd(buf, 200);
	ft_putstr_fd(s, 1);
	ft_putchar_fd('\n', 1);
	return (0);
}
