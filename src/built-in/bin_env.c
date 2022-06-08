/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:30:53 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/08 19:35:28 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bin_env(t_commands cmd)
{
	t_list	*lst;

	(void)cmd;
	lst = g_env;
	while (lst)
	{
		printf("%s\n", lst->content);
		lst = lst->next;
	}
	return (1);
}
