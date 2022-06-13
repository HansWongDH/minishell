/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:05:55 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/13 21:29:02 by wding-ha         ###   ########.fr       */
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
	free(newpwd);
}

// int	cur_dir(void)
// {
// 	char	buf[200];
// 	char	*oldpwd;

// 	getcwd(buf, 200);
// 	oldpwd = ft_getenv("PWD");
// 	chdir(buf);
// 	pwd_change(oldpwd, buf);
// 	free(oldpwd);
// 	return (0);
// }

// int	find_path(char *s)
// {
// 	int	i;
// 	int	ret;

// 	i = 0;
// 	ret = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == '/')
// 			ret = i;
// 		i++;
// 	}
// 	return (ret);
// }

// int	up_dir(void)
// {
// 	char	buf[200];
// 	char	*dir;
// 	int		i;
// 	int		ret;

// 	i = 0;
// 	ret = 0;
// 	getcwd(buf, 200);
// 	while (buf[i])
// 	{
// 		if (buf[i] == '/')
// 			ret = i;
// 		i++;
// 	}
// 	dir = ft_substr(buf, 0, ret + 1);
// 	chdir(dir);
// 	pwd_change(buf, dir);
// 	free(dir);
// 	return (0);
// }

int	change_dir(char *s)
{
	if (!ft_strcmp(s, "."))
		return (0);
	if (chdir(s) < 0)
		return (error_msg(1, "NO such file or directory\n"));
	return (0);
}

int	bin_cd(t_command cmd)
{
	char	*dir;
	char	*home;
	t_list	*lst;
	char	buf[200];

	dir = ft_getenv("PWD");
	lst = cmd.args;
	if (!lst)
	{
		home = ft_getenv("HOME");
		if (!home)
			return (error_msg(1, "cd: HOME not set\n"));
		chdir(home);
		free(home);
	}
	else
	{
		if (change_dir(*(char **)lst->content))
			return (1);
	}
	pwd_change(dir, getcwd(buf, 200));
	free(dir);
	return (0);
}
