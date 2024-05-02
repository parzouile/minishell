/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanacze <jbanacze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 23:26:18 by jules             #+#    #+#             */
/*   Updated: 2024/05/02 19:32:03 by jbanacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO - Setup empty env -> set PWD, SHLVL=0
int	setup_empty_env(t_env *env)
{
	if (add_value(env, "SHLVL=0"))
		return (1);
	return (0);
}

int	setup_env(t_env *env, char **envp, int top)
{
	if (!envp)
		return (1);
	if (!envp[0] && top)
		return (setup_empty_env(env));
	if (!envp[0])
		return (0);
	if (add_value(env, envp[0]))
		return (1);
	return (setup_env(&((*env)->next), envp + 1, 0));
}

int	incr_shlvl(t_env env)
{
	int		shlvl;
	char	*n_shlvl;

	env = get_node(env, "SHLVL");
	if (!env)
		return (1);
	shlvl = ft_atoi(env->value) + 1;
	n_shlvl = ft_itoa(shlvl);
	if (!n_shlvl)
		return (1);
	free(env->value);
	env->value = n_shlvl;
	return (0);
}
