/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_sleep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:56:13 by aschmitt          #+#    #+#             */
/*   Updated: 2024/03/21 14:04:45 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
#include "minishell.h"


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
	exit(1);
	return (NULL);
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

char	*find_bin(char *cmd, char **envp)
{
	char	**path;
	char	*bin;
	int		i;

	i = 0;
	path = find_paths(envp);
	while (path[i])
	{
		bin = ft_join(path[i], cmd);
		if (access(bin, F_OK) == 0)
		{
			return (bin);
		}
		free(bin);
		i++;
	}
	return (NULL);
}

void	command(char *cmd, char **envp)
{
	char	**args;
	char	*bin;

	args = ft_split(cmd, ' ');
	bin = find_bin(args[0], envp);
	execve(bin, args, envp);
}

void	test_sleep(char **envp)
{
	pid_t	pid;
	pid = fork();
	if (pid == 0)
	{
		command("sleep 10", envp);
	}
	wait(&pid);
}
