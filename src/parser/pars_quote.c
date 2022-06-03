/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:42:26 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/03 21:46:22 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_strjoin2d(char **s, char **str)
{
	int		i;
	char	*temp;

	i = 0;
	while (str[i])
	{
		temp = *s;
		*s = ft_strjoin(temp, str[i]);
		free(temp);
		i++;
	}
	free2d(str);
}

char	*quote_extract(char *s)
{
	char	*ret;
	char	**temp;
	char	*str;
	int		i;
	int		start;

	i = 0;
	ret = ft_calloc(1, 1);
	start = i;
	while (s[i])
	{
		if (is_quote(s[i]))
		{
			check_quote(s, &i, s[i]);
			str = ft_substr(s, start, i + 1 - start);
			temp = ft_split(str, s[i]);
			free(str);
			ft_strjoin2d(&ret, temp);
			if (s[i] == '\"')
				ret = env_extract(ret, 1);
			start = i + 1;
		}
		i++;
	}
	if (s[start])
		ret = ft_strjoin(ret, (s + start));
	return (ret);
}

void	quote_treatment(char **s)
{
	int		i;
	char	*temp;

	i = 0;
	while (s[i])
	{
		if (ft_strchr(s[i], '\'') || ft_strchr(s[i], '\"'))
		{
			temp = quote_extract(s[i]);
			free(s[i]);
			s[i] = ft_strdup(temp);
			free(temp);
		}
		i++;
	}
}
