/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:37:01 by aschmitt          #+#    #+#             */
/*   Updated: 2024/04/30 10:29:04 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmpn(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i ++;
	if (!s2[i] && s1[i] == '\n')
		return (0);
	return (s1[i] - s2[i]);
}

void	write_here_doc(char *limiter, int fd)
{
	char	*s;

	s = readline(">> ");
	while (ft_strcmpn(s, limiter) != 0)
	{
		write(fd, s, ft_strlen(s));
		write(fd, "\n", 1);
		if (s)
			free(s);
		s = readline(">> ");
	}
	if (s)
		free(s);
	close(fd);
}

int	get_here_doc(char *limiter)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		ft_error("Pipe");
	write_here_doc(limiter, pipefd[1]);
	return (pipefd[0]);
}

pid_t	ft_exec2(t_minishell mini, t_command cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (0); // error
	else if (pid == 0)
	{
		dup2(cmd.infile, STDIN_FILENO);
		dup2(cmd.outfile, STDOUT_FILENO);
		if (builtin(mini, cmd, mini->envp) == 1)
		{
			execve(cmd.cmd, cmd.args, mini->envp);
			error_msg("minishell: command not found\n");
		}
		exit(0);
	}
	return (pid);
}
