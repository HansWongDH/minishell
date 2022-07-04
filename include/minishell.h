/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:36:31 by wding-ha          #+#    #+#             */
/*   Updated: 2022/07/04 20:35:34 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <termios.h>
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
typedef struct s_redir {
	char			**file;
	int				red;
}	t_redir;

typedef struct s_command {
	char	**token;
	char	**cmd;
	t_list	*args;
	t_list	*redir;
	int		fd;
}	t_command;

/*command group in linkedlist form*/
typedef struct s_cmdlist {
	struct s_command	cmd;
	struct s_cmdlist	*next;
}	t_cmdlist;

typedef struct s_shell {
	int				dstdin;
	int				dstdout;
	int				pipe;
	int				i;
	int				fd[2];
	struct termios	ori;
	struct termios	new;
}	t_shell;

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
t_command	*struct_init(t_command *cmd);
void		command_table_init(char **s, int *i, t_command *cmd);
t_cmdlist	*cmdlist_init(char **s);

/*Utility function for commandlist*/
void		ft_cmdadd_back(t_cmdlist **lst, t_cmdlist *new);
t_cmdlist	*ft_newcmd(t_command cmd);

/*Utility function : free memory*/
void		free2d(char **s);
char		*ft_strjoinfree(char *s1, char *s2);
char		**ft_strjoin2d(char **args, char *s, int i);
char		*ft_combine_key(char *s1, char *s2, char c);

/*Quote removal and expansion of environmental variable*/
void		quote_treatment(char **s);
void		env_treatment(char **s);
char		*env_extract(char *s, int qt);
char		*ft_getenv(char *s);
void		cmdlist_expansion(t_cmdlist *list);
void		set_cmd(t_cmdlist *cmd);
int			parse_cmd(t_cmdlist *lst, t_shell *sh);
void		env_build(char **envp);
char		*add_quote_heredoc(char *s);

/*lexer initalization*/
t_cmdlist	*lexer_init(char *s);

/*built-in : export*/
int			ft_envcmp(const char *s1, const char *s2);
int			export_str(char *s);
int			bin_export(t_command cmd);

/*built-in : echo*/
int			bin_echo(t_command cmd);

/*built-in : unset*/
int			bin_unset(t_command cmd);
void		remove_env(char *s);
/*built-in : env*/
int			bin_env(t_command cmd);

int			bin_exit(t_command cmd);

int			bin_pwd(t_command cmd);

int			bin_cd(t_command cmd);

void		free_cmdlist(t_cmdlist **cmd);
/*For error handling*/
int			error_msg(int i, int fd, char *args, char *s);
void		*token_error(char **s);

int			execute(t_command cmd, t_shell *sh);
int			redir_dup(t_command cmd);
void		parse_heredoc(t_cmdlist *cmd);
int			parse_cmdline(t_cmdlist *lst, t_shell *sh);
int			check_builtin(t_command cmd);
void		export_exit(int i);
t_shell		init(void);
int			waitforchild(int pid);

/* For signal handling */
void		ctrl_c(int signo);
int			executor(t_command cmd, t_shell *sh);

#endif
