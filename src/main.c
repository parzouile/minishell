/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:13:51 by aschmitt          #+#    #+#             */
/*   Updated: 2024/04/29 11:42:30 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * to complete
*/
void	ft_exit(void)
{
	rl_clear_history();
	exit(0);
}

void	ft_ctrls(int sig)
{
	(void)sig;
}


int	run_minishell(t_minishell mini)
{
	char	*s;

	using_history();
	s = readline("\033[32;1m$ User ->\033[0m ");
	while (s && mini->exit == -1)
	{
		add_history(s);
		if (!parse(mini, s))
		{
			// print_token(mini->cmd_line);
			if (mini->cmd_line)
				start_exe(mini);
			// print_token(mini->cmd_line);
			// printf("exit : %d\n", mini->exit);
		}
		free_tokens(mini->cmd_line);
		mini->cmd_line = NULL;
		free(s);
		if (mini->exit == -1)
			s = readline("\033[32;1m$ User ->\033[0m ");
	}
	if (mini->exit == -1)
		mini->exit = 0;
	return (mini->exit);
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
	rl_clear_history();
	return (exit_status);
}
