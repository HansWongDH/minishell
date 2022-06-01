/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:02:16 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/01 21:32:10 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_fetch(char *s, int *i)
{
	char	*temp;
	char	*ret;
	int		start;

	start = *i;
	while (ft_isalnum(s[*i]))
		(*i)++;
	temp = ft_substr(s, start, *i - start);
	ret = getenv(temp);
	free(temp);
	return (ret);
}

char	*env_extract(char *s)
{
	int		i;
	int		start;
	char	*temp;
	char	*ret;

	i = 0;
	start = i;
	while (s[i])
	{
		if (s[i] == '$')
		{	
			if (i > 0)
				ret = ft_substr(s, start, i - start);
			// printf("%s\n", ret);
			i++;
			temp = env_fetch(s, &i);
			// printf("%s\n", temp);
			ret = ft_strjoin(ret, temp);
			start = i;
		}
		else
			i++;
	}
	return (ret);
}
