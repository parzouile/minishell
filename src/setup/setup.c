/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:38:51 by jules             #+#    #+#             */
/*   Updated: 2024/04/08 17:13:35 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_env(t_env *env, char **envp)
{
	if (!)
	*env = malloc(sizeof(struct s_env));
	if (!(*env))
		return (1);
	
	
}

t_minishell	create_minishell(char **envp)
{
	t_minishell	mini;

	mini = malloc(sizeof(struct s_minishell));
	if (!mini)
		return (NULL);
	mini->cmd_line = NULL;
	mini->env = NULL;
	setup_env(&(mini->env), envp);
	if (envp && !(mini->env))
	{
		free(mini);
		return (NULL);
	}
	return (mini);
}