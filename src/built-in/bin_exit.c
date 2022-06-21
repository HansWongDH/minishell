/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:53:21 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/21 13:34:56 by wding-ha         ###   ########.fr       */
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
		exit(error_msg(ex, 2, "", "exit"));
	if (!exit_number(*(char **)lst->content))
		exit(error_msg(0, 2, "", "exit"));
	if (exit_number(*(char **)lst->content) == 255)
	{
		ft_putstr_fd("exit\n", 2);
		exit(error_msg(255, 2, "exit", ": numeric argument required"));
	}
	else if (ft_lstsize(lst) > 1)
		return (error_msg(1, 2, "exit", "too many arguments"));
	else
	{
		ft_putstr_fd("exit\n", 2);
		ex = ft_atoi(*(char **)lst->content);
	}
	exit(ex % 256);
}
