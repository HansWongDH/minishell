/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:36:31 by wding-ha          #+#    #+#             */
/*   Updated: 2022/05/26 21:20:38 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include "libft.h"

typedef struct s_data {
	char	**input;
	int		red;
	int		pipe;
	int		heredoc;
}	t_data;

typedef struct s_token {
	t_data			*content;
	struct s_token	*next;
}	t_token;

int	token_length(char *s);
int	check_quote(char *s, int *i, int c);
int	check_command(char	*s, int *i, int c);
char	**split_token(char *s, int size);
int	is_command(char c);
int	syntax_checking(char **s);

#endif
