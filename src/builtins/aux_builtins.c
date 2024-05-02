/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:14:03 by aschmitt          #+#    #+#             */
/*   Updated: 2024/05/02 17:20:45 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cut_last_slash(char *str)
{
	int	i;
	int	index_last_slash;

	i = 0;
	index_last_slash = 0;
	if (!str)
		return ;
	while (str[i])
	{
		if (str[i] == '/')
			index_last_slash = i;
		i++;
	}
	str[index_last_slash + 1] = 0;
}

char	*get_value_cd(t_env env, char *key)
{
	if (!key)
	{
		return (NULL);
	}
	if (!env)
	{
		return (NULL);
	}
	if (ft_strcmp(env->name, key) == 0)
	{
		return (ft_strdup(env->value));
	}
	return (get_value_cd(env->next, key));
}

void	ft_envp(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		printf("%s\n", envp[i]);
}

void	ft_pwd(void)
{
	char	buffer[2048];

	getcwd(buffer, 2048);
	printf("%s\n", buffer);
}
