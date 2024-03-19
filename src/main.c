/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:13:51 by aschmitt          #+#    #+#             */
/*   Updated: 2024/03/18 16:29:46 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t ctrlc_pressed = 0;

void	ft_exit() 
{
	rl_clear_history();
	printf("\033[31;1mBye\033[0m\n");
	exit(0);
}

void	ft_test()
{
	printf("\n\033[32;1m$ User ->\033[0m ");
	ctrlc_pressed = 1;
}

void	display_prompt()
{
	char	*s;

	s = NULL;
	using_history();
	signal(2, ft_test);
	while (1)
	{
		if (ctrlc_pressed) {
            ctrlc_pressed = 0;
			continue ;
		}
		s = readline("\033[32;1m$ User ->\033[0m ");
		if (!s)
			ft_exit();
		add_history(s);
		parsing(&s);
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