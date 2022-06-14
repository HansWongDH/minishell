/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:40:17 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/14 19:30:23 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char		*str;
	t_cmdlist	*list;
	int			ex;

	(void)ac;
	(void)av;
	ex = 0;
	env_build(envp);
	signal(SIGINT, SIG_IGN);
	while (1)
	{
		str = readline("Minishell⌲ ");
		add_history(str);
		list = lexer_init(str, ex);
		if (list)
		{
			ex = parse_cmd(list, ex);
			free_cmdlist(list);
		}
		free(str);
	}
}
