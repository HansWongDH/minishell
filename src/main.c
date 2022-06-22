/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echai <echai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:40:17 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/22 16:15:05 by echai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	init(void)
{
	t_shell			sh;

	sh.ex = 0;
	sh.dstdin = dup(0);
	sh.dstdout = dup(1);
	tcgetattr(0, sh.ori);
	sh.new->c_cflag = ECHOCTL;
	tcsetattr(0, TCSANOW, sh.new);
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
	while (1)
	{
		signal(SIGINT, &ctrl_c);
		signal(SIGQUIT, SIG_IGN);
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
