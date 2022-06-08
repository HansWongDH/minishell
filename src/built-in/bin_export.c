/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:05:32 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/08 19:42:39 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	*export_noargs(t_commands *cmd)

int	export_str(char *s)
{
	int		i;
	char	*env;

	i = 0;
	while (s[i] != '=')
	{
		if (!ft_isalpha(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	env = ft_substr(s, 0, i);
	if (!ft_getenv(env))
		ft_lstadd_back(&g_env, ft_lstnew(ft_strdup(s)));
	free(env);
	return (1);
}

int	bin_export(t_commands cmd)
{
	t_list	*lst;

	lst = cmd.args;
	if (!lst)
		return (-1);
	while (lst)
	{
		if (!ft_strchr(lst->content, '='))
			return (error_msg(-1, "Error not a valid identifier"));
		if (!export_str(lst->content))
			return (error_msg(-1, "Error not a valid identifier"));
		lst = lst->next;
	}
	return (1);
}
