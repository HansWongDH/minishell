/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:53:21 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/14 19:28:19 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_number(char *s)
{
	int	i;

	i = 0;
	if (!ft_strcmp(s, "--"))
		return (0);
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (255);
		i++;
	}
	return (1);
}

int	bin_exit(t_command cmd, int ex)
{
	t_list	*lst;

	lst = cmd.args;
	if (!lst)
		exit(error_msg(ex, "exit\n"));
	if (!exit_number(*(char **)lst->content))
		exit(error_msg(0, "exit\n"));
	if (exit_number(*(char **)lst->content) == 255)
		exit(error_msg(255, "exit: numeric argument required\n"));
	else if (ft_lstsize(lst) > 1)
		return (error_msg(1, "exit: too many arguments\n"));
	else
	{
		ft_putstr_fd("exit\n", 1);
		ex = ft_atoi(*(char **)lst->content);
	}
	exit(ex % 256);
}
