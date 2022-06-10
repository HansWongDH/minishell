/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:04:50 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/10 17:43:37 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_env(char *s)
{
	t_list	*lst;
	t_list	*key;

	lst = g_env;
	while (lst && lst->next)
	{
		if (!ft_envcmp(lst->next->content, s))
		{
			key = lst->next;
			lst->next = key->next;
			free(key);
		}
		lst = lst->next;
	}
}

int	check_key(char *s)
{
	int	i;

	i = 0;
	if (ft_isalpha(s[i]) || s[i] == '_')
		i++;
	while (ft_isalnum(s[i]) || s[i] == '_')
		i++;
	if (s[i])
		return (0);
	return (1);
}

int	bin_unset(t_command cmd)
{
	t_list	*lst;
	int		error;
	char	*value;

	lst = cmd.args;
	error = 0;
	while (lst)
	{
		if (!check_key(lst->content))
			error = 1;
		value = ft_getenv(lst->content);
		if (value)
		{
			remove_env(lst->content);
			free(value);
		}
		lst = lst->next;
	}
	if (error)
		return (error_msg(-1, "Error: not a valid identifier\n"));
	return (1);
}
