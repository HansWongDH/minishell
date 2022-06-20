/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:55:48 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/14 18:29:48 by wding-ha         ###   ########.fr       */
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
	int		len;
	char	*ret;
	int		size;
	t_list	*lst;

	ret = NULL;
	len = ft_strlen(s);
	lst = g_env;
	while (lst)
	{
		if (!ft_envcmp(lst->content, s))
		{
			size = ft_strlen(lst->content);
			ret = ft_substr(lst->content, len + 1, size - len + 1);
		}
		lst = lst->next;
	}
	return (ret);
}
