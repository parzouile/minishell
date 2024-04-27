/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:38:51 by jules             #+#    #+#             */
/*   Updated: 2024/04/26 17:24:40 by aschmitt         ###   ########.fr       */
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

int	run_minishell(t_minishell mini)
{
	(void) mini;
	t_token token1;
	t_token token2;
	t_token token3;
	t_token token4;
	
	token4 = malloc(sizeof(struct s_token));
	token1 = malloc(sizeof(struct s_token));
	token2 = malloc(sizeof(struct s_token));
	token3 = malloc(sizeof(struct s_token));
	token1->str = "pwd";
	token2->str = "src";
	token3->str = "|";
	token4->str = "/bin/ls";
	
	token1->type = 0;
	token2->type = 2;
	token3->type = 7;
	token4->type = 1;
	
	token1->prev = NULL;
	token1->next = token2;
	token2->prev = token1;
	token2->next = token3;
	token3->prev = token2;
	token3->next = token4;
	token4->prev = token3;
	token4->next = NULL;
	mini->cmd_line = token1;
	start_exe(mini);

	// token1->str = "env";
	// token2->str = "src/";
	// token3->str = "test";
	// token4->str = "/bin/wc";
	
	// token1->type = 0;
	// token2->type = 2;
	// token3->type = 5;
	// token4->type = 1;
	
	// token1->prev = NULL;
	// token1->next = NULL;//token2;
	// token2->prev = token1;
	// token2->next = 	token3;
	// token3->prev = token2;
	// token3->next = NULL; // token4;
	// token4->prev = token3;
	// token4->next = NULL;
	// mini->cmd_line = token1;
	// start_exe(mini);
	
	free(token1);
	free(token2);
	free(token3);
	free(token4);
	
	return (0);
}
