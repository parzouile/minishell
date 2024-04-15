/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanacze <jbanacze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:36:28 by jbanacze          #+#    #+#             */
/*   Updated: 2024/04/15 14:55:50 by jbanacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	env_len(t_env env)
{
	if (!env)
		return (0);
	return (1 + env_len->next);
}

char	**tenv_to_arr(t_env	env)
{
	char	**envp;
	size_t	i;
	size_t	len;

	len = env_len(env) + 1;
	envp = malloc(sizeof(char *) * len);
	if (!envp)
		return (NULL);
	i = 0;
	while (i < len)
	{
		envp[i] = env->value;
		env = env->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
