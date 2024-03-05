/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:13:51 by aschmitt          #+#    #+#             */
/*   Updated: 2024/03/05 13:19:13 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_exit() 
{
	exit(0);
}


void	display_prompt(void)
{
	char	*s;

	while (1)
	{
		s = readline("\033[32;1mUser\033[0m: ");
		add_history(s);
		ft_putstr_fd(s, 1);
        ft_putstr_fd("\n", 1);
		parsing(s);
		free(s);
	}
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;

	
	display_prompt();
}