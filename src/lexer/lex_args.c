/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 13:32:31 by wding-ha          #+#    #+#             */
/*   Updated: 2022/05/27 21:53:53 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_symbol(char *s)
{
	if (!ft_strcmp(s, ">"))
		return (OUTFILE);
	if (!ft_strcmp(s, ">>"))
		return (DOUTFILE);
	if (!ft_strcmp(s, "<"))
		return (INFILE);
	if (!ft_strcmp(s, "<<"))
		return (HEREDOC);
	if (!ft_strcmp(s, "|"))
		return (PIPE);
	return (0);
}

int	syntax_checking(char **s)
{
	int	i;

	i = 0;
	if (parse_symbol(s[i]) == PIPE)
		return (-1);
	while (s[i])
	{
		if (parse_symbol(s[i]) && (parse_symbol(s[i + 1]) || !s[i + 1]))
			return (-1);
		i++;
	}
	return (0);
}

char	**ft_divide(char **s, int len)
{
	char	**ret;
	int		i;

	i = 0;
	ret = ft_calloc(sizeof(char *), len + 1);
	while (i < len)
	{
		ret[i] = ft_strdup(s[i]);
		i++;
	}
	return (ret);
}

t_commands struct_init(void)
{
	t_commands	cmd;

	cmd.args = NULL;
	cmd.infile = NULL;
	cmd.outfile = NULL;
	cmd.num = 0;
	cmd.sym_in = 0;
	cmd.sym_out = 0;
	return (cmd);
}

t_commands	command_table_init(char **s)
{
	int			i;
	t_commands	cmd;

	i = 0;
	cmd = struct_init();
	if (!s)
		return (cmd);
	while (parse_symbol(s[i]) != PIPE && s[i])
	{
		if (parse_symbol(s[i]) == OUTFILE || parse_symbol(s[i]) == DOUTFILE)
		{
			cmd.sym_out = parse_symbol(s[i]);
			if (cmd.outfile)
				free(cmd.outfile);
			cmd.outfile = ft_strdup(s[i + 1]);
		}
		if (parse_symbol(s[i]) == INFILE || parse_symbol(s[i]) == HEREDOC)
		{
			cmd.sym_in = parse_symbol(s[i]);
			if (cmd.infile)
				free(cmd.infile);
			printf("cur %d\n", i + 1);
			cmd.infile = ft_strdup(s[i + 1]);
		}
		i++;
	}
	cmd.num = i;
	cmd.args = ft_divide(s, i);
	return (cmd);
}
