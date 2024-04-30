/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:38:09 by aschmitt          #+#    #+#             */
/*   Updated: 2024/04/30 10:30:07 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **path)
{
	int	i;

	i = -1;
	while (path[++i])
		free(path[i]);
	free(path);
}

char	*ft_join(char *s1, char *s2)
{
	char	*result;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	result = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!result)
		return (NULL);
	i = -1;
	while (s1[++i])
		result[i] = s1[i];
	result[i++] = '/';
	j = -1;
	while (s2[++j])
		result[i + j] = s2[j];
	result[i + j] = '\0';
	return (result);
}

char	**find_paths(t_env env)
{
	char	*s;
	char	**path;

	s = get_value(env, "PATH");
	if (s)
	{
		path = ft_split(s, ':');
		free(s);
		return (path);
	}
	write(2, "Error Path\n", 12);
	return (NULL);
}

char	*find_bin(char *cmd, t_env env)
{
	char	**path;
	char	*bin;
	int		i;

	i = 0;
	path = find_paths(env);
	if (!path)
		return (cmd);
	while (path[i])
	{
		bin = ft_join(path[i], cmd);
		if (!bin)
			return (free_tab(path), cmd);
		if (access(bin, F_OK) == 0)
		{
			free(cmd);
			free_tab(path);
			return (bin);
		}
		free(bin);
		i++;
	}
	free_tab(path);
	return (cmd);
}
