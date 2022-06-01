/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:40:17 by wding-ha          #+#    #+#             */
/*   Updated: 2022/06/01 19:34:22 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmdlist	*lexer_init(char *s)
{
	int			i;
	char		**token;
	t_cmdlist	*list;

	i = token_length(s);
	if (i < 0)
		return (NULL);
	token = split_token(s, i);
	if (!token)
		return (NULL);
	quote_treatment(token);
	list = cmdlist_init(token);
	return (list);
}

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
		system("leaks minishell");
		return (0);
	}
}
