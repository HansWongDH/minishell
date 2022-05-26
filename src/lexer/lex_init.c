/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:36:13 by wding-ha          #+#    #+#             */
/*   Updated: 2022/05/26 21:06:49 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

static int	is_del(char c)
{
	if (c == ' ' || c == '\0')
		return (1);
	return (0);
}

static int	is_args(char c)
{
	if (!is_del(c) && !is_command(c))
		return (1);
	return (0);
}

int	token_length(char *s)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (is_quote(s[i]) && check_quote(s, &i, s[i]) < 0)
			return (-1);
		if (is_command(s[i]))
		{
			if (check_command(s, &i, s[i]) < 0)
				return (-1);
			else
				len++;
		}
		if (is_args(s[i]) && !is_args(s[i + 1]))
			len++;
		i++;
	}
	return (len);
}

char	*split_command(char *s, int *i)
{
	char	*ret;
	int		len;
	int		start;

	start = *i;
	len = check_command(s, i, s[*i]);
	ret = ft_substr(s, start, len);
	return (ret);
}

char	**split_token(char *s, int size)
{
	int		i;
	int		len;
	int		start;
	char	**ret;

	i = 0;
	len = 0;
	ret = ft_calloc(sizeof(char *), size + 1);
	while (len < size)
	{
		start = i;
		while (is_args(s[i]))
			i++;
		if (is_quote(s[i]) && check_quote(s, &i, s[i]) != -1)
			i++;
		if (i - start > 0 && !is_args(s[i]))
			ret[len++] = ft_substr(s, start, i - start);
		if (is_command(s[i]))
			ret[len++] = split_command(s, &i);
		i++;
	}
	return (ret);
}
