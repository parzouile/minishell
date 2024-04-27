/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:07:49 by jbanacze          #+#    #+#             */
/*   Updated: 2024/04/27 20:43:06 by jules            ###   ########.fr       */
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
	return (1);
}
