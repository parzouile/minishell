/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:38:51 by jules             #+#    #+#             */
/*   Updated: 2024/04/29 11:28:19 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	create_minishell(char **envp)
{
	t_minishell	mini;
	int			error;

	mini = malloc(sizeof(struct s_minishell));
	if (!mini)
		return (NULL);
	mini->cmd_line = NULL;
	mini->env = NULL;
	error = setup_env(&(mini->env), envp);
	if (error)
	{
		free_env(mini->env);
		free(mini);
		return (NULL);
	}
	if (incr_shlvl(mini->env))
		printf("INCREMENT SHLVL FAILED\n");
	mini->exit = -1;
	return (mini);
}

void	free_minishell(t_minishell mini)
{
	if (!mini)
		return ;
	free_tokens(mini->cmd_line);
	free_env(mini->env);
	free(mini);
}
