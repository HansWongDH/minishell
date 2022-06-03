/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:42:26 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/04 03:06:37 by wding-ha         ###   ########.fr       */
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
		*s = ft_strjoinfree(temp, str[i]);
		i++;
	}
	free(str);
}

char	*quote_extract(char *s)
{
	char	*ret;
	char	**temp;
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
			temp = ft_splitfree(ft_substr(s, start, i + 1 - start), s[i]);
			ft_strjoin2d(&ret, temp);
			if (s[i] == '\"')
				ret = env_extract(ret, 1);
			start = i + 1;
		}
		i++;
	}
	ret = ft_strjoinfree(ret, ft_substr(s, start, start - i));
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
