/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 13:32:31 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/04 03:36:34 by wding-ha         ###   ########.fr       */
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
		if (parse_symbol(s[i]) > 1 && (parse_symbol(s[i + 1]) || !s[i + 1]))
			return (error_msg(-1, "Syntax error: redirection\n"));
		if (parse_symbol(s[i]) == PIPE)
		{
			if (parse_symbol(s[i + 1]) == PIPE || !s[i + 1])
				return (error_msg(-1, "Syntax error: pipe\n"));
		}
		i++;
	}
	return (1);
}

char	**ft_divide(char **s, int len, int i)
{
	char	**ret;
	int		j;

	j = 0;
	ret = ft_calloc(sizeof(char *), len + 1);
	while (j < len)
	{
		ret[j] = ft_strdup(s[i]);
		i++;
		j++;
	}
	return (ret);
}

t_commands	*struct_init(t_commands *cmd)
{
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->num = 0;
	cmd->sym_in = 0;
	cmd->sym_out = 0;
	return (cmd);
}

void	command_table_init(char **s, int *i, t_commands *cmd)
{
	int			start;

	start = *i;
	while (parse_symbol(s[*i]) != PIPE && s[*i])
	{
		if (parse_symbol(s[*i]) == OUTFILE || parse_symbol(s[*i]) == DOUTFILE)
		{
			cmd->sym_out = parse_symbol(s[*i]);
			if (cmd->outfile)
				free(cmd->outfile);
			cmd->outfile = ft_strdup(s[*i + 1]);
		}
		if (parse_symbol(s[*i]) == INFILE || parse_symbol(s[*i]) == HEREDOC)
		{
			cmd->sym_in = parse_symbol(s[*i]);
			if (cmd->infile)
				free(cmd->infile);
			cmd->infile = ft_strdup(s[*i + 1]);
		}
		(*i)++;
	}
	cmd->num = *i - start;
	cmd->args = ft_divide(s, cmd->num, start);
}
