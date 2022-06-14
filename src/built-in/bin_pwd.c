/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:59:42 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/14 19:05:07 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bin_pwd(t_command cmd)
{
	char	buf[200];

	(void)cmd;
	if (cmd.args)
		return (error_msg(1, "pwd: too many arguments\n"));
	printf("%s\n", getcwd(buf, 200));
	return (0);
}
