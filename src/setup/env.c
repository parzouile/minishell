/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanacze <jbanacze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:07:49 by jbanacze          #+#    #+#             */
/*   Updated: 2024/04/24 13:27:55 by jbanacze         ###   ########.fr       */
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
	if (env->value)
		free(env->value);
	free(env);
	free_env(next);
}

int	add_value(t_env *env, char *str)
{
	t_env	new;

	if (!str || !env)
		return (1);
	new = malloc(sizeof(struct s_env));
	if (!new)
		return (1);
	new->next = NULL;
	new->value = strdup(str);
	if (new->value)
		return (free_env(new), 1);
	new->next = *env;
	*env = new;
	return (0);
}

char	*get_value(t_env env, char *str)
{
	if (!env || !str)
		return (ft_calloc(1, sizeof(char)));
	if ()
	
}
