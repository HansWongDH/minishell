/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 02:23:26 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/20 20:22:10 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoinfree(char *s1, char *s2)
{
	char	*ret;

	ret = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (ret);
}

char	*ft_combine_key(char *s1, char *s2, char c)
{
	char	*ret;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	ret = ft_calloc(len + 1, sizeof(char));
	while (s1[j])
		ret[i++] = s1[j++];
	ret[i] = c;
	i++;
	j = 0;
	while (s2[j])
		ret[i++] = s2[j++];
	free(s1);
	free(s2);
	return (ret);
}

char	**ft_strjoin2d(char **args, char *s, int i)
{
	int		len;
	int		j;
	char	**ret;

	len = 0;
	j = 0;
	while (args[len])
		len++;
	if (i > len - 1)
		return (NULL);
	ret = ft_calloc(len + 2, sizeof(char *));
	while (j < len)
	{
		if (j == i)
			ret[j++] = ft_strdup(s);
		ret[j++] = ft_strdup(*args);
		args++;
	}
	return (ret);
}
