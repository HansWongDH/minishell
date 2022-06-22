/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echai <echai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:40:17 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/22 14:30:26 by echai            ###   ########.fr       */
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

/**
 * @brief Main function
 * 
 * @param ac Argument count
 * @param av Argument variables
 * @param envp Environment variables
 * @return int Exit code
 */
int	main(int ac, char **av, char **envp)
{
	char		*str;
	t_cmdlist	*list;
	t_shell		sh;

	(void)ac;
	(void)av;
	sh = init();
	env_build(envp);
	signal(SIGINT, &ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		str = readline("Minishell⌲ ");
		if (!str)
			break ;
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
