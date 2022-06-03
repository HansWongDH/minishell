/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:36:31 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/03 21:42:44 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

# define PIPE 1
# define OUTFILE 2
# define DOUTFILE 3
# define INFILE 4
# define HEREDOC 5


typedef struct s_command {
	char	**args;
	int		num;
	char	*infile;
	int		sym_in;
	char	*outfile;
	int		sym_out;
}	t_commands;

typedef struct s_cmdlist {
	struct s_command	cmd;
	struct s_cmdlist	*next;
}	t_cmdlist;

int		token_length(char *s);
char	*split_symbol(char *s, int *i);
int		check_quote(char *s, int *i, int c);
int		check_symbol(char	*s, int *i, int c);
char	**split_token(char *s, int size);
int		is_symbol(char c);
int		syntax_checking(char **s);
t_commands	*struct_init(t_commands *cmd);
int		is_quote(char c);
void	command_table_init(char **s, int *i, t_commands *cmd);
int		parse_symbol(char *s);
t_cmdlist	*cmdlist_init(char **s);
void	free2d(char **s);
void	quote_treatment(char **s);
char	*env_extract(char *s, int qt);
void	env_treatment(char **s);
void	cmdlist_expansion(t_cmdlist *list);

#endif
