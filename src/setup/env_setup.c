/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 23:26:18 by jules             #+#    #+#             */
/*   Updated: 2024/04/27 02:06:37 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO - Setup empty env -> set PWD, SHLVL=0
int	setup_empty_env(t_env *env)
{
	(void) env;
	return (0);
}

int	setup_env(t_env *env, char **envp)
{
	if (!envp)
		return (1);
	if (!envp[0])
		return (setup_empty_env(env));
	if (add_value(env, envp[0]))
		return (1);
	return (setup_env(&((*env)->next), envp + 1));
}

int	incr_shlvl(t_env env)
{
	int		shlvl;
	char	*n_shlvl;

	if (!env)
		return (1);
	if (ft_strcmp(env->name, "SHLVL") == 0)
	{
		shlvl = ft_atoi(env->value) + 1;
		n_shlvl = ft_itoa(shlvl);
		if (!n_shlvl)
			return (1);
		free(env->value);
		env->value = n_shlvl;
		return (0);
	}
	return (incr_shlvl(env->next));
}
