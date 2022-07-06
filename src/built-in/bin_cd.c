/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:05:55 by wding-ha          #+#    #+#             */
/*   Updated: 2022/07/06 14:11:35 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_change(char *oldpath, char *newpath)
{
	char	*oldpwd;
	char	*newpwd;	

	if (oldpath)
	{
		oldpwd = ft_strjoin("OLDPWD=", oldpath);
		export_str(oldpwd);
		free(oldpwd);
		free(oldpath);
	}
	if (newpath)
	{
		newpwd = ft_strjoin("PWD=", newpath);
		export_str(newpwd);
		free(newpwd);
		free(newpath);
	}
}

int	change_dir(char *s)
{
	char	*dir;
	char	*newdir;

	if (!ft_strcmp(s, "-"))
	{
		s = ft_getenv("OLDPWD");
		if (!s)
			return (error_msg(1, 2, "cd", ": OLDPWD not set"));
	}
	dir = ft_getenv("PWD");
	if (chdir(s) < 0)
	{
		free(dir);
		return (error_msg(1, 2, s, ": No such file or directory"));
	}
	newdir = ft_getenv("PWD");
	pwd_change(dir, newdir);
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
