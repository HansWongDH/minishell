/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:53:21 by wding-ha          #+#    #+#             */
/*   Updated: 2022/07/06 14:16:36 by wding-ha         ###   ########.fr       */
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
			return (2);
		i++;
	}
	return (1);
}

int	get_exit(void)
{
	char	*s;
	int		i;

	s = ft_getenv("?");
	i = ft_atoi(s);
	free(s);
	return (i);
}

int	bin_exit(t_command cmd)
{
	t_list	*lst;
	int		ex;

	ex = get_exit();
	lst = cmd.args;
	if (!lst)
		exit(error_msg(ex, 1, "", "exit"));
	if (!exit_number(*(char **)lst->content))
		exit(error_msg(0, 1, "", "exit"));
	if (exit_number(*(char **)lst->content) == 2)
	{
		ft_putstr_fd("exit\n", 1);
		exit(error_msg(255, 2, "exit", ": numeric argument required"));
	}
	else if (ft_lstsize(lst) > 1)
		return (error_msg(1, 2, "exit\n", "too many arguments"));
	else
	{
		ft_putstr_fd("exit\n", 1);
		ex = ft_atoi(*(char **)lst->content);
	}
	exit(ex % 256);
}
