/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:07:49 by jbanacze          #+#    #+#             */
/*   Updated: 2024/04/24 23:55:37 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_value(t_env *env, char *str)
{
	t_env	new;
	int		i;

	if (!str || !env)
		return (1);
	i = -1;
	while (str[++i])
		if (str[i] == '=')
			break ;
	if (!i || !str[i])
		return (2);
	new = malloc(sizeof(struct s_env));
	if (!new)
		return (1);
	new->next = NULL;
	new->name = ft_substr(str, 0, i);
	new->value = ft_strdup(str + i + 1);
	if (!new->value || !new->name)
		return (free_env(new), 1);
	new->next = *env;
	*env = new;
	return (0);
}

int	setup_env(t_env *env, char **envp)
{
	if (!envp)
		return (1);
	if (!envp[0])
		return (0);
	if (add_value(env, envp[0]))
	{
		printf("%s\n", envp[0]);
		return (1);
	}
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
	if (env->name)
		free(env->name);
	free(env);
	free_env(next);
}

// char	*get_value(t_env env, char *str)
// {
// 	if (!env)
// 		return (ft_calloc(1, sizeof(char)));
// 	if (ft_strcmp(env->name, str) == 0)
// 		return (ft_strdup(env->value));
// }
