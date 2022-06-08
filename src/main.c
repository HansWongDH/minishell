/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:40:17 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/08 19:13:11 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char		*str;
	t_cmdlist	*list;
	(void)ac;
	(void)av;
	while (1)
	{
		str = readline("Minishell⌲ ");
		if (!str)
			return (0);
		env_build(envp);
		add_history(str);
		list = lexer_init(str);
		free(str);
		parse_cmd(list);
		// while (g_env[i])
		// 	printf("%s\n", g_env[i++]);
		// while (list)
		// {
		// 	j = 0;
		// 	while(list->cmd.args[j])
		// 	{
		// 		printf("%s\n", list->cmd.args[j]);
		// 		j++;
		// 	}
		// 	printf("infile is %s\noutfile is %s\n", list->cmd.infile, list->cmd.outfile);
		// 	printf("----------------\n");
		// 	list = list->next;
		// }
		// while (head)
		// {
		// 	t_cmdlist	*temp;

		// 	free2d(head->cmd.args);
		// 	free(head->cmd.infile);
		// 	free(head->cmd.outfile);
		// 	temp = head;
		// 	head = head->next;
		// 	free(temp);
	}
}
