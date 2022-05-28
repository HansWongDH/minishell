/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:40:17 by wding-ha          #+#    #+#             */
/*   Updated: 2022/05/28 15:50:56 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char		*str;
	char		**token;
	int			i;
	int 		j;
	t_cmdlist	*list;
	t_cmdlist	*head;

	while (1)
	{
		str = readline("Minishell %");
		add_history(str);
		i = token_length(str);
		printf("token length is %d\n", i);
		token = split_token(str, i);
		list = cmdlist_init(token);
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
			temp = head;
			head = head->next;
			free(temp);
		}
	}
}
