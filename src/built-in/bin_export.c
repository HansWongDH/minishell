/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:05:32 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/10 17:45:31 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_print(char	*s)
{
	int		i;
	int		start;
	char	*key;
	char	*value;

	i = 0;
	start = i;
	while (s[i])
	{
		if (s[i] == '=')
			break ;
		i++;
	}
	key = ft_substr(s, start, i + 1);
	value = ft_substr(s, i + 1, ft_strlen(s) - i - 1);
	printf("declare -x %s\"%s\"\n", key, value);
	free(key);
	free(value);
}

int	export_noargs(void)
{
	t_list	*export;

	export = g_env;
	while (export)
	{
		export_print(export->content);
		export = export->next;
	}
	return (0);
}

int	export_str(char *s)
{
	int		i;
	char	*env;
	char	*value;

	i = 0;
	if (ft_isalpha(s[i]) || s[i] == '_')
		i++;
	else
		return (0);
	while (s[i] != '=' && s[i])
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	env = ft_substr(s, 0, i);
	value = ft_getenv(env);
	if (value)
		remove_env(env);
	ft_lstadd_back(&g_env, ft_lstnew(s));
	free(env);
	return (1);
}

int	bin_export(t_command cmd)
{
	t_list	*lst;
	int		error;

	lst = cmd.args;
	error = 0;
	if (!lst)
		return (export_noargs());
	while (lst)
	{
		// if (!ft_strchr(lst->content, '='))
		// 	error = 1;
		if (!export_str(lst->content))
			error = 1;
		lst = lst->next;
	}
	if (error)
		return (error_msg(1, "Error: not a valid identifier\n"));
	return (0);
}
