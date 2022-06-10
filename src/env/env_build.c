/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:26:40 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/10 15:43:15 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_build(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_lstadd_back(&g_env, ft_lstnew(envp[i]));
		i++;
	}
}
