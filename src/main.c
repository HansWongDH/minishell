/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:40:17 by wding-ha          #+#    #+#             */
/*   Updated: 2022/05/27 21:51:07 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	main(void)
{
	char	*str;
	char	**token;
	t_commands	cmd;
	int		i;
	int		j;

	while (1)
	{
		str = readline("Minishell %");
		add_history(str);
		i = token_length(str);
		printf("token is %d\n", i);
		token = split_token(str, i);
		cmd = command_table_init(token);
		j = 0;
		while (cmd.args[j])
		{
			printf("%s \n", cmd.args[j]);
			j++;
		}
		printf("infile is %d, %s\n outfile is %d, %s\n total num of argument is %d\n", cmd.sym_in, cmd.infile, cmd.sym_out, cmd.outfile, cmd.num);
	}
}
