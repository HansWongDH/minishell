/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:26:40 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/14 14:01:48 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
