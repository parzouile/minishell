/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:13:51 by aschmitt          #+#    #+#             */
/*   Updated: 2024/03/13 13:57:14 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_exit() 
{
	rl_clear_history();
	printf("\n\033[31;1mBye\033[0m\n");
	exit(0);
}


void	display_prompt(void)
{
	char	*s;

	signal(2, ft_exit);
	using_history();
	while (1)
	{
		s = readline("\033[32;1m$ User ->\033[0m ");
		add_history(s);
		parsing(s);
		free(s);
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;

	
	display_prompt();
}