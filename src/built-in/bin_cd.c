/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:05:55 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/23 20:56:24 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_change(char *oldpath, char *newpath)
{
	char	*oldpwd;
	char	*newpwd;

	oldpwd = ft_strjoin("OLDPWD=", oldpath);
	newpwd = ft_strjoin("PWD=", newpath);
	export_str(oldpwd);
	export_str(newpwd);
	free(oldpwd);
	free(oldpath);
	free(newpwd);
}

int	change_dir(char *s)
{
	char	*dir;
	char	buf[200];

	if (!ft_strcmp(s, "-"))
	{
		s = ft_getenv("OLDPWD");
		if (!s)
			return (error_msg(1, 2, "cd", ": OLDPWD not set"));
	}
	dir = ft_getenv("PWD");
	if (!dir)
		dir = getcwd(buf, 200);
	if (chdir(s) < 0)
		return (error_msg(1, 2, s, ": No such file or directory"));
	pwd_change(dir, getcwd(buf, 200));
	return (0);
}

int	bin_cd(t_command cmd)
{
	char	*dir;
	t_list	*lst;

	lst = cmd.args;
	if (!lst)
	{
		dir = ft_getenv("HOME");
		if (!dir)
			return (error_msg(1, 2, "cd", ": HOME not set"));
	}
	else
		dir = ft_strdup(*(char **)lst->content);
	if (change_dir(dir))
	{
		free(dir);
		return (1);
	}
	free(dir);
	return (0);
}
