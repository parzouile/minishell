/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:38:51 by jules             #+#    #+#             */
/*   Updated: 2024/04/15 10:19:30 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_env(t_env *env, char **envp)
{
	if (!envp)
		return (1);
	if (!envp[0])
		return (0);
	*env = malloc(sizeof(struct s_env));
	if (!(*env))
		return (1);
	(*env)->next = NULL;
	(*env)->value = strdup(envp[0]);
	if (!(*env)->value && envp[0])
		return (1);
	return (setup_env(&((*env)->next), envp + 1));
}

void	free_env(t_env env)
{
	t_env	next;

	if (!env)
		return ;
	next = env->next;
	free(env->value);
	free(env);
	free_env(next);
}

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
	return (mini);
}

void	free_minishell(t_minishell mini)
{
	if (!mini)
		return ;
	free_env(mini->env);
	free(mini);
}

int	run_minishell(t_minishell mini, char **envp)
{
	(void) mini;
	start_exe(mini, envp);
	return (0);
}
