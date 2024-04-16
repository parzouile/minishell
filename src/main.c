/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:13:51 by aschmitt          #+#    #+#             */
/*   Updated: 2024/04/16 12:24:22 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(void)
{
	rl_clear_history();
	printf("\033[31;1mBye\033[0m\n");
	exit(0);
}

void	ft_error(char *s)
{
	perror(s);
	exit(1);
}

void	ft_ctrls(int sig)
{
	(void)sig;
}

void	display_prompt(char **envp)
{
	char	*s;

	(void)envp;
	s = NULL;
	using_history();
	signal(SIGINT, ft_ctrlc);
	signal(SIGQUIT, ft_ctrls);
	while (1)
	{
		s = readline("\033[32;1m$ User ->\033[0m ");
		if (!s)
			ft_exit();
		add_history(s);
		parsing(&s, envp);
		free(s);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	mini;
	int			exit_status;

	(void)av;
	if (ac != 1)
	{
		(void) write(2, "Error args\n", 11);
		return (EXIT_FAILURE);
	}
	mini = create_minishell(envp);
	if (!mini)
	{
		(void) write(2, "Error during setup\n", 19);
		return (EXIT_FAILURE);
	}
	exit_status = run_minishell(mini);
	free_minishell(mini);
	return (exit_status);
}
