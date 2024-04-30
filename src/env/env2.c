/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:16:08 by jules             #+#    #+#             */
/*   Updated: 2024/04/30 18:07:31 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	env_len(t_env env)
{
	if (!env)
		return (0);
	return (1 + env_len(env->next));
}

char	**tenv_to_arr(t_env	env)
{
	char	**envp;
	char	*tmp;
	size_t	i;
	size_t	len;

	len = env_len(env) + 1;
	envp = malloc(sizeof(char *) * len);
	if (!envp)
		return (NULL);
	i = 0;
	while (i + 1 < len)
	{
		tmp = ft_strjoin(env->name, "=");
		if (!tmp)
			return (NULL);
		envp[i] = ft_strjoin(tmp, env->value);
		if (!envp[i])
			return (free(tmp), NULL);
		free(tmp);
		env = env->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

int	is_valid_name(char *str)
{
	int	i;

	i = -1;
	if (!str || !is_valid_char(str[0]) || ft_isdigit(str[0]))
		return (0);
	while (str[++i])
	{
		if (str[i] == '=')
			break ;
		if (!is_valid_char(str[i]))
			return (0);
	}
	return (i);
}

t_env	get_node(t_env env, char *key)
{
	if (!env)
		return (NULL);
	if (ft_strcmp(env->name, key) == 0)
		return (env);
	return (get_node(env->next, key));
}

int	modify_node_value(t_env env, char *key, char *new_value)
{
	if (!env || !key || !new_value)
		return (1);
	if (ft_strcmp(env->name, key) == 0)
	{
		free(env->value);
		env->value = new_value;
		return (0);
	}
	return (modify_node_value(env->next, key, new_value));
}
