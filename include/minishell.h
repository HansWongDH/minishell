/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:36:31 by wding-ha          #+#    #+#             */
/*   Updated: 2022/05/27 20:14:49 by wding-ha         ###   ########.fr       */
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

# define OUTFILE 1
# define DOUTFILE 2
# define INFILE 3
# define HEREDOC 4
# define PIPE 5

typedef struct s_command {
	char	**args;
	int		num;
	char	*infile;
	int		sym_in;
	char	*outfile;
	int		sym_out;
}	t_commands;

typedef struct s_cmdlist {
	struct s_command	*simple_command;
	struct s_cmdlist	*next;

}	t_cmdlist;

int		token_length(char *s);
char	*split_symbol(char *s, int *i);
int		check_quote(char *s, int *i, int c);
int		check_symbol(char	*s, int *i, int c);
char	**split_token(char *s, int size);
int		is_symbol(char c);
int		syntax_checking(char **s);
t_commands	command_table_init(char **s);

#endif
