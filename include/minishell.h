/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:36:31 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/08 19:38:14 by wding-ha         ###   ########.fr       */
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

t_list	*g_env;
/*
Simple command table
args	-token in 2D char array
num		-number of argument
infile	-filename for infile
outfile	-filename for outfile
sym_in	-type of infile redic
sym_out	-type of outfile redic
*/

typedef struct s_command {
	char	**token;
	int		num;
	char	*infile;
	int		sym_in;
	char	*outfile;
	int		sym_out;
	char	*cmd;
	t_list	*args;
	char	**red;
}	t_commands;

/*command group in linkedlist form*/
typedef struct s_cmdlist {
	struct s_command	cmd;
	struct s_cmdlist	*next;
}	t_cmdlist;

/*Splitting string into 2D array token*/
int			token_length(char *s);
char		*split_symbol(char *s, int *i);
char		**split_token(char *s, int size);

/*Syntax checking for input string*/
int			is_quote(char c);
int			is_symbol(char c);
int			check_quote(char *s, int *i, int c);
int			check_symbol(char *s, int *i, int c);

/*Syntax checking for token after splitting*/
int			syntax_checking(char **s);
int			parse_symbol(char *s);

/*Initialize command table */
t_commands	*struct_init(t_commands *cmd);
void		command_table_init(char **s, int *i, t_commands *cmd);
t_cmdlist	*cmdlist_init(char **s);

/*Utility function for commandlist*/
void		ft_cmdadd_back(t_cmdlist **lst, t_cmdlist *new);
t_cmdlist	*ft_newcmd(t_commands cmd);

/*Utility function : free memory*/
void		free2d(char **s);
char		*ft_strjoinfree(char *s1, char *s2);
char		**ft_splitfree(char *s, char c);

/*Quote removal and expansion of environmental variable*/
void		quote_treatment(char **s);
void		env_treatment(char **s);
char		*env_extract(char *s, int qt);
char		*ft_getenv(char *s);
void		cmdlist_expansion(t_cmdlist *list);
void		set_cmd(t_cmdlist *cmd);
void		parse_cmd(t_cmdlist *lst);
void		env_build(char **envp);

/*lexer initalization*/
t_cmdlist	*lexer_init(char *s);

/*built-in : export*/
int			ft_envcmp(const char *s1, const char *s2);
int			bin_export(t_commands cmd);

/*built-in : echo*/
int			bin_echo(t_commands cmd);

/*built-in : env*/
int			bin_env(t_commands cmd);
/*For error handling*/
int			error_msg(int i, char *s);
void		*token_error(char **s);

#endif
