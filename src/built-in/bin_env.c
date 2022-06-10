/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:30:53 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/10 17:30:18 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bin_env(t_command cmd)
{
	t_list	*lst;
	int		i;

	i = 0;
	(void)cmd;
	lst = g_env;
	while (lst)
	{
		printf("%s\n", lst->content);
		lst = lst->next;
	}
	return (0);
}
