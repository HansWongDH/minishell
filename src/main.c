/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:40:17 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/24 01:56:34 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	init(void)
{
	t_shell			sh;

	sh.ex = 0;
	sh.dstdin = dup(0);
	sh.dstdout = dup(1);
	tcgetattr(STDIN_FILENO, &sh.ori);
	tcgetattr(STDIN_FILENO, &sh.new);
	sh.new.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &sh.new);
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
	env_build(envp);
	while (1)
	{
		sh = init();
		signal(SIGINT, &ctrl_c);
		signal(SIGQUIT, SIG_IGN);
		str = readline("Minishell⌲ ");
		if (!str)
			break ;
		add_history(str);
		list = lexer_init(str, &sh);
		if (list)
			sh.ex = parse_cmdline(list, &sh);
		free(str);
	}
	system("leaks minishell");
}
