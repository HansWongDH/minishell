/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:15:22 by wding-ha          #+#    #+#             */
/*   Updated: 2022/07/06 14:47:33 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_newline(char *s)
{
	int	i;

	i = 0;
	if (!s[i])
		return (1);
	if (s[i] == '-')
		i++;
	while (s[i] == 'n')
		i++;
	if (!s[i] && i > 1)
		return (1);
	return (0);
}

int	bin_echo(t_command cmd)
{
	t_list	*lst;
	int		nl;

	lst = cmd.args;
	nl = 1;
	while (lst && echo_newline(*(char **)lst->content))
	{
		lst = lst->next;
		nl = 0;
	}
	while (lst)
	{
		ft_putstr_fd(*(char **)lst->content, 1);
		if (lst->next)
			ft_putchar_fd(32, 1);
		lst = lst->next;
	}
	if (nl && !lst)
		ft_putchar_fd('\n', 1);
	return (0);
}
