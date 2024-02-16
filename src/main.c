/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:13:51 by aschmitt          #+#    #+#             */
/*   Updated: 2024/02/16 14:30:11 by aschmitt         ###   ########.fr       */
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
		ft_putstr_fd("\033[32;1m", 1);
		ft_putstr_fd("gaga", 1);
		ft_putstr_fd("@\033[0m: ", 1);
		s = get_next_line(0);
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