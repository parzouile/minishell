/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanacze <jbanacze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:38:51 by jules             #+#    #+#             */
/*   Updated: 2024/05/02 10:33:56 by jbanacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_minishell(t_minishell mini)
{
	if (!mini)
		return ;
	free_tokens(mini->cmd_line);
	free_env(mini->env);
	if (mini->s)
		free(mini->s);
	if (mini->envp)
		free_tab(mini->envp);
	free(mini);
}

t_minishell	create_minishell(char **envp)
{
	t_minishell	mini;
	int			error;

	g_current_status = 0;
	mini = malloc(sizeof(struct s_minishell));
	if (!mini)
		return (NULL);
	mini->cmd_line = NULL;
	mini->env = NULL;
	mini->s = NULL;
	mini->envp = NULL;
	error = setup_env(&(mini->env), envp);
	if (error)
		return (free_minishell(mini), NULL);
	if (incr_shlvl(mini->env))
		return (free_minishell(mini), NULL);
	return (mini);
}
