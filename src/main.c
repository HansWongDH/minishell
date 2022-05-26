/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:40:17 by wding-ha          #+#    #+#             */
/*   Updated: 2022/05/26 21:23:50 by wding-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*str;
	char	**token;
	int		i;
	int		j;

	while (1)
	{
		str = readline("Minishell %");
		i = token_length(str);
		printf("token is %d\n", i);
		token = split_token(str, i);
		j = 0;
		while (token[j])
			printf("%s \n", token[j++]);
		printf("syntax checking %d\n", syntax_checking(token));
	}
}
