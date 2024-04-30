/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:13:51 by aschmitt          #+#    #+#             */
/*   Updated: 2024/04/30 18:00:39 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_current_status;

void	ft_exit(void)
{
	rl_clear_history();
	exit(0);
}

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
		if (runner->type == CMD)
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
	char	*s;

	using_history();
	assign_sig_handler(SIG_MAIN);
	s = readline("\033[32;1m$ User ->\033[0m ");
	while (s && mini->exit == -1)
	{
		assign_sig_handler(SIG_MAIN);
		add_history(s);
		if (!parse(mini, s))
		{
			find_cmd(mini);
			if (mini->cmd_line)
				start_exe(mini);
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
