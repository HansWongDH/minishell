/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echai <echai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:42:26 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/20 12:52:40 by echai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Extracts quotes
 * 
 * @param s 
 * @param ex 
 * @return char* 
 */
char	*quote_extract(char *s, int ex)
{
	char	*ret;
	char	*temp;
	int		i;
	int		start;

	i = 0;
	ret = ft_calloc(1, 1);
	start = i;
	while (s[i])
	{
		if (is_quote(s[i]))
		{
			ret = ft_strjoinfree(ret, ft_substr(s, start, i - start));
			temp = (ft_substr(s, i + 1, check_quote(s, &i, s[i])));
			if (s[i] == '\"')
				temp = env_extract(temp, 1, ex);
			ret = ft_strjoinfree(ret, temp);
			start = i + 1;
		}
		i++;
	}
	ret = ft_strjoinfree(ret, ft_substr(s, start, start - i));
	return (ret);
}

/**
 * @brief 
 * 
 * @param s 
 * @param ex 
 */
void	quote_treatment(char **s, int ex)
{
	int		i;
	char	*temp;

	i = 0;
	while (s[i])
	{
		if (ft_strchr(s[i], '\'') || ft_strchr(s[i], '\"'))
		{
			temp = quote_extract(s[i], ex);
			free(s[i]);
			s[i] = ft_strdup(temp);
			free(temp);
		}
		i++;
	}
}
