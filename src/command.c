/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 09:54:21 by aschmitt          #+#    #+#             */
/*   Updated: 2024/03/22 11:28:18 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*args_path(char *args)
{
	int		i;
	int		a;
	char	*s;

	i = -1;
	a = 0;
	while (args[++i])
	{
		if (args[i] == '/')
			a = i;
	}
	s = malloc(sizeof(char) * (i - a));
	if (!s)
		return (NULL);
	i = -1;
	while (args[++a])
		s[++i] = args[a];
	s[++i] = 0;
	free (args);
	return (s);
}

char	**find_paths(char **envp, char **args)
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
	free_tab(args);
	write(2, "Error Path\n", 12);
	exit(1);
	return (NULL);
}

char	*find_bin(char *cmd, char **envp, char **args)
{
	char	**path;
	char	*bin;
	int		i;

	i = 0;
	path = find_paths(envp, args);
	if (!path)
		{printf("test"), ft_error("Malloc");}
	while (path[i])
	{
		bin = ft_join(path[i], cmd);
		if (!bin)
            (free_tab(args), free_tab(path), ft_error("Malloc"));
		if (access(bin, F_OK) == 0)
		{
			free_tab(path);
			return (bin);
		}
		free(bin);
		i++;
	}
	free_tab(args);
	free_tab(path);
	ft_error("Command not found");
	return (NULL);
}

void	processus(int new_pipe[2], int pipefd[2], char *cmd, char **envp)
{
	dup2(new_pipe[1], STDOUT_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	close(new_pipe[0]);
	command(cmd, envp);
	close(pipefd[0]);
	close(new_pipe[1]);
	ft_error("Execution");
}

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

void	command(char *cmd, char **envp)
{
	char	**args;
	char	*bin;

	args = ft_split(cmd, ' ');
	if (!args)
		ft_error("Malloc");
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		bin = ft_strdup(args[0]);
		args[0] = args_path(args[0]);
	}
	else
		bin = find_bin(args[0], envp, args);
	if (execve(bin, args, envp) == -1)
		ft_error("Execution");
}
