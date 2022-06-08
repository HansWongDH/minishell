/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:55:48 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/08 14:24:02 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_envcmp(const char *s1, const char *s2)
{
	size_t	i;

	if (!s1)
		return (0);
	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
	{
		if (s1[i + 1] == '=' && !s2[i + 1])
			break ;
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_getenv(char *s)
{
	int		i;
	int		len;
	char	*ret;

	ret = ft_calloc(1, 1);
	len = ft_strlen(s);
	i = 0;
	while (g_env[i])
	{
		if (!ft_envcmp(g_env[i], s))
			ret = ft_substr(g_env[i], len + 1, ft_strlen(g_env[i]) - len + 1);
		i++;
	}
	return (ret);
}
