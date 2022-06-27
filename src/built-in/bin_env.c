/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:30:53 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/27 15:54:30 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bin_env(t_command cmd)
{
	t_list	*lst;

	(void)cmd;
	lst = g_env;
	while (lst)
	{
		if (ft_envcmp((char *)lst->content, "?"))
			printf("%s\n", (char *)lst->content);
		lst = lst->next;
	}
	return (0);
}
