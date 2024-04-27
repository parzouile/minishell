/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:13:51 by aschmitt          #+#    #+#             */
/*   Updated: 2024/04/27 01:39:54 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(void)
{
	rl_clear_history();
	printf("\033[31;1mBye\033[0m\n");
	exit(0);
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

int	run_minishell(t_minishell mini)
{
	char	*s;

	using_history();
	s = readline("\033[32;1m$ User ->\033[0m ");
	while (s)
	{
		add_history(s);
		if (parse(mini, s))
			return (free(s), 1);
		free(s);
		//exec(mini);
		print_token(mini->cmd_line);
		free_tokens(mini->cmd_line);
		mini->cmd_line = NULL;
		s = readline("\033[32;1m$ User ->\033[0m ");
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	mini;
	int			exit_status;

	(void)av;
	if (ac != 1)
		return (error_msg("Error args\n"));
	mini = create_minishell(envp);
	if (!mini)
		return (error_msg("Error during setup\n"));
	exit_status = run_minishell(mini);
	free_minishell(mini);
	return (exit_status);
}
