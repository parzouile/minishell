/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:05:18 by aschmitt          #+#    #+#             */
/*   Updated: 2024/03/22 13:04:03 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_lentab(char **tab)
{
	int	i;

	if (!tab)
		return (0);
	i = 0;
	while (tab[i])
		i++;
	return (i);
}
