/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:46:16 by wding-ha          #+#    #+#             */
/*   Updated: 2022/05/28 15:50:04 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote(char *s, int *i, int c)
{
	int	len;

	len = 0;
	if (s[*i] == c)
		(*i)++;
	while (s[*i] != c && s[*i])
	{
		(*i)++;
		len++;
	}
	if (s[*i] == c)
		return (len);
	return (-1);
}

int	is_symbol(char c)
{
	if (c == '>' || c == '<')
		return (1);
	if (c == '|')
		return (2);
	return (0);
}

int	check_symbol(char	*s, int *i, int c)
{
	int	len;

	len = 1;
	if (is_symbol(c) == 1 && s[*i + 1] == c)
	{
		(*i)++;
		len++;
	}
	if (c == '|' && s[*i + 1] == c)
		return (-1);
	if (is_symbol(c) == 1 && is_symbol(s[*i + 1]))
		return (-1);
	return (len);
}

char	*split_symbol(char *s, int *i)
{
	char	*ret;
	int		len;
	int		start;

	start = *i;
	len = check_symbol(s, i, s[*i]);
	ret = ft_substr(s, start, len);
	return (ret);
}

