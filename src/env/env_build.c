/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:26:40 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/23 23:39:48 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function helps you build an env linked list
 * 
 * @param envp Pointer to env variables
 */
void	env_build(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_envcmp(envp[i], "OLDPWD"))
			i++;
		ft_lstadd_back(&g_env, ft_lstnew(ft_strdup(envp[i])));
		i++;
	}
}
