/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:40:17 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/04 04:08:03 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char		*str;
	int 		j;
	t_cmdlist	*list;
	t_cmdlist	*head;

	while (1)
	{
		str = readline("Minishell⌲ ");
		add_history(str);
		list = lexer_init(str);
		free(str);
		head = list;
		while (list)
		{
			j = 0;
			while(list->cmd.args[j])
			{
				printf("%s\n", list->cmd.args[j]);
				j++;
			}
			printf("infile is %s\n outfile is %s\n", list->cmd.infile, list->cmd.outfile);
			printf("----------------\n");
			list = list->next;
		}
		while (head)
		{
			t_cmdlist	*temp;

			free2d(head->cmd.args);
			free(head->cmd.infile);
			free(head->cmd.outfile);
			temp = head;
			head = head->next;
			free(temp);
		}
		return (0);
	}
}
