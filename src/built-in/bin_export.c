/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:05:32 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/27 15:43:59 by wding-ha         ###   ########.fr       */
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
	char	*s;

	export = g_env;
	while (export)
	{
		export_print(export->content);
		if (export->next && !ft_envcmp(export->next->content, "PWD"))
		{
			s = ft_getenv("OLDPWD");
			if (!s)
				printf("declare -x OLDPWD\n");
			else
				free(s);
		}
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
	{
		remove_env(env);
		free(value);
	}
	ft_lstadd_back(&g_env, ft_lstnew(ft_strdup(s)));
	free(env);
	return (1);
}

int	bin_export(t_command cmd)
{
	t_list	*lst;
	char	*error;

	lst = cmd.args;
	error = NULL;
	if (!lst)
		return (export_noargs());
	while (lst)
	{
		if (!export_str(*(char **)lst->content))
			error = *(char **)lst->content;
		lst = lst->next;
	}
	if (error)
		return (error_msg(1, 2, error, ": not a valid identifier"));
	return (0);
}
