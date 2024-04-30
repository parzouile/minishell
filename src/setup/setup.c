/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanacze <jbanacze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:38:51 by jules             #+#    #+#             */
/*   Updated: 2024/04/30 15:19:18 by jbanacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	error = setup_env(&(mini->env), envp);
	if (error)
	{
		free_env(mini->env);
		free(mini);
		return (NULL);
	}
	if (incr_shlvl(mini->env))
		printf("INCREMENT SHLVL FAILED\n");
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
