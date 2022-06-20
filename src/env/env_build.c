/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echai <echai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:26:40 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/20 11:54:38 by echai            ###   ########.fr       */
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
		ft_lstadd_back(&g_env, ft_lstnew(envp[i]));
		i++;
	}
}
