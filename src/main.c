/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:13:51 by aschmitt          #+#    #+#             */
/*   Updated: 2024/03/05 14:07:57 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_exit() 
{
	clear_history();
	exit(0);
}


void	display_prompt(void)
{
	char	*s;

	while (1)
	{
		s = readline("\033[32;1mUser\033[0m: ");
		add_history(s);
		parsing(s);
		free(s);
		signal(2, ft_exit);
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;

	
	display_prompt();
}