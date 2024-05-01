/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:13:51 by aschmitt          #+#    #+#             */
/*   Updated: 2024/05/01 18:19:22 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_current_status;

void	ft_ctrls(int sig)
{
	(void)sig;
}

void	find_cmd(t_minishell mini)
{
	t_token	runner;

	runner = (mini->cmd_line);
	while (runner)
	{
		if (runner->type == CMD && runner->str && runner->str[0])
		{
			if (!is_builtin(runner->str))
			{
				if (runner->str[0] != '/' && runner->str[0] != '.')
					runner->str = find_bin(runner->str, mini->env);
			}
		}
		runner = runner->next;
	}
}

int	run_minishell(t_minishell mini)
{
	using_history();
	assign_sig_handler(SIG_MAIN);
	mini->s = readline("\033[32;1m$ User ->\033[0m ");
	while (mini->s)
	{
		assign_sig_handler(SIG_MAIN);
		add_history(mini->s);
		if (!parse(mini, mini->s))
		{
			find_cmd(mini);
			if (mini->cmd_line)
				start_exe(mini);
		}
		else
			g_current_status = 2;
		free_tokens(mini->cmd_line);
		mini->cmd_line = NULL;
		free(mini->s);
		mini->s = NULL;
		mini->s = readline("\033[32;1m$ User ->\033[0m ");
	}
	return (g_current_status);
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
	printf("exit\n");
	rl_clear_history();
	return (exit_status);
}
