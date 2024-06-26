/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:07:49 by jbanacze          #+#    #+#             */
/*   Updated: 2024/04/30 10:37:21 by aschmitt         ###   ########.fr       */
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

t_env	remove_from_env(t_env env, char *key)
{
	t_env	next;

	if (!key)
		return (env);
	if (!env)
		return (NULL);
	if (ft_strcmp(env->name, key) == 0)
	{
		next = env->next;
		if (env->value)
			free(env->value);
		if (env->name)
			free(env->name);
		free(env);
		return (next);
	}
	env->next = remove_from_env(env->next, key);
	return (env);
}

char	*get_value(t_env env, char *key)
{
	if (!key)
		return (NULL);
	if (!env)
		return (ft_calloc(1, sizeof(char)));
	if (ft_strcmp(env->name, key) == 0)
		return (ft_strdup(env->value));
	return (get_value(env->next, key));
}
