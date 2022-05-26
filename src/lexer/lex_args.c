/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 13:32:31 by wding-ha          #+#    #+#             */
/*   Updated: 2022/05/26 21:25:10 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_command(char *s)
{
	if (!ft_strcmp(s, ">>") || !ft_strcmp(s, ">"))
		return (1);
	if (!ft_strcmp(s, "<<") || !ft_strcmp(s, "<"))
		return (2);
	if (!ft_strcmp(s, "|"))
		return (3);
	return (0);
}

int	syntax_checking(char **s)
{
	int	i;

	i = 0;
	if (parse_command(s[0]))
		return (-1);
	while (s[i])
	{
		if (parse_command(s[i]) && (parse_command(s[i + 1]) || !s[i + 1]))
			return (-1);
		i++;
	}
	return (0);
}
