/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:15:22 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/08 19:28:08 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bin_echo(t_commands cmd)
{
	t_list	*lst;

	lst = cmd.args;
	while (lst)
	{
		ft_putstr_fd(lst->content, 1);
		if (lst->next)
			ft_putchar_fd(32, 1);
		else
			ft_putchar_fd('\n', 1);
		lst = lst->next;
	}
	return (1);
}
