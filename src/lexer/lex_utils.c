/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:46:16 by wding-ha          #+#    #+#             */
/*   Updated: 2022/05/26 18:07:02 by wding-ha         ###   ########.fr       */
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

int	is_command(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

int	check_command(char	*s, int *i, int c)
{
	int	len;

	len = 1;
	if ((c == '>' || c == '<') && s[*i + 1] == c)
	{
		(*i)++;
		len++;
	}
	if (is_command(s[*i + 1]))
		return (-1);
	return (len);
}
