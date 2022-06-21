/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:40:17 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/21 20:39:19 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	init(void)
{
	t_shell	sh;

	sh.ex = 0;
	sh.dstdin = dup(0);
	sh.dstdout = dup(1);
	return (sh);
}

int	main(int ac, char **av, char **envp)
{
	char		*str;
	t_cmdlist	*list;
	t_shell		sh;

	(void)ac;
	(void)av;
	sh = init();
	env_build(envp);
	signal(SIGINT, SIG_IGN);
	while (1)
	{
		str = readline("Minishell⌲ ");
		add_history(str);
		list = lexer_init(str, &sh);
		if (list)
		{
			sh.ex = parse_cmdline(list, &sh);
			free_cmdlist(list);
		}
		free(str);
	}
}
