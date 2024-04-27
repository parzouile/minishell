/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:38:09 by aschmitt          #+#    #+#             */
/*   Updated: 2024/04/27 16:44:42 by aschmitt         ###   ########.fr       */
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

char	**find_paths(char **envp)
{
	int		i;
	int		a;
	char	*s;

	i = -1;
	s = "PATH=";
	while (envp[++i])
	{
		a = 0;
		while (envp[i][a] && s[a] && envp[i][a] == s[a])
			a ++;
		if (a == 5)
			break ;
	}
	if (a == 5)
		return (ft_split(envp[i] + 5, ':'));
	write(2, "Error Path\n", 12);
	return (NULL);
}

char	*find_bin(char *cmd, char **env)
{
	char	**path;
	char	*bin;
	int		i;

	i = 0;
	path = find_paths(env);
	if (!path)
		return (NULL);
	while (path[i])
	{
		bin = ft_join(path[i], cmd);
		if (!bin)
			return (free_tab(path), NULL);
		if (access(bin, F_OK) == 0)
		{
			free_tab(path);
			return (bin);
		}
		free(bin);
		i++;
	}
	free_tab(path);
	write(2, "Command not found\n", 19);
	return (NULL);
}