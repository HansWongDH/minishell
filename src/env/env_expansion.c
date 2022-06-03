/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:02:16 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/04 03:08:39 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_addquote(char c)
{
	char	*ret;
	char	add;
	int		i;

	i = 0;
	ret = ft_calloc(4, 1);
	if (c == '\'')
		add = '\"';
	else
		add = '\'';
	while (i < 3)
	{
		if (i % 2 == 0)
			ret[i] = add;
		else
			ret[i] = c;
		i++;
	}
	return (ret);
}

char	*env_isquote(char *s)
{
	int		i;
	int		start;
	char	*ret;
	char	*temp;

	i = 0;
	start = i;
	ret = ft_calloc(1, 1);
	while (s[i])
	{
		if (is_quote(s[i]))
		{
			temp = ft_substr(s, start, i - start);
			ret = ft_strjoinfree(ret, temp);
			ret = ft_strjoinfree(ret, env_addquote(s[i]));
			start = i + 1;
		}
		i++;
	}
	ret = ft_strjoinfree(ret, ft_substr(s, start, i - start));
	return (ret);
}

char	*env_fetch(char *s, int *i, int qt)
{
	char	*temp;
	char	*ret;
	int		start;

	start = *i;
	while (ft_isalnum(s[*i]))
		(*i)++;
	temp = ft_substr(s, start, *i - start);
	ret = (getenv(temp));
	free(temp);
	if (!ret)
		ret = ft_calloc(1, 1);
	else
		ret = ft_strdup(ret);
	if (qt == 0 && (ft_strchr(ret, '\'') || ft_strchr(ret, '\"')))
		ret = env_isquote(ret);
	return (ret);
}

char	*env_extract(char *s, int qt)
{
	int		i;
	int		start;
	char	*ret;

	i = 0;
	ret = ft_calloc(1, 1);
	start = i;
	while (s[i])
	{
		if (qt == 0 && is_quote(s[i]) && check_quote(s, &i, s[i]))
			i++;
		else if (s[i] == '$')
		{	
			if (start != i)
				ret = ft_strjoinfree(ret, ft_substr(s, start, i - start));
			i++;
			ret = ft_strjoinfree(ret, env_fetch(s, &i, qt));
			start = i;
		}
		else
			i++;
	}
	ret = ft_strjoinfree(ret, ft_substr(s, start, i - start));
	free(s);
	return (ret);
}

void	env_treatment(char **s)
{
	int		i;
	char	*temp;

	i = 0;
	while (s[i])
	{
		if (ft_strchr(s[i], '$'))
		{
			temp = env_extract(s[i], 0);
			s[i] = ft_strdup(temp);
			free(temp);
		}
		i++;
	}
}