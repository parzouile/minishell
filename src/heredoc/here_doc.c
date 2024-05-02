/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:01:03 by aschmitt          #+#    #+#             */
/*   Updated: 2024/05/02 16:36:57 by aschmitt         ###   ########.fr       */
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

int	write_here_doc(char *limiter, int fd, t_minishell mini, int n)
{
	char	*s;

	while (1)
	{
		write(1, "> ", 2);
		s = get_next_line(0);
		if (s == NULL || ft_strcmpn(s, limiter) == 0 || g_current_status == 130)
			break ;
		if (!n)
			s = expand_heredoc(mini, s);
		write(fd, s, ft_strlen(s));
		free(s);
	}
	close(fd);
	if (g_current_status == 130)
	{
		if (s)
			free(s);
		return (1);
	}
	if (s)
		free(s);
	else
		error_here_doc(limiter);
	return (0);
}

int	get_here_doc(char *limiter, t_minishell mini, t_command *cmd, int n)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		return (-1);
	assign_sig_handler(SIG_HEREDOC);
	cmd->exec = write_here_doc(limiter, pipefd[1], mini, n);
	return (pipefd[0]);
}

void	zero_command(t_minishell mini)
{
	t_command	command;

	command.exec = 0;
	if (redirection(&command, &mini->cmd_line, mini) == 0)
		return (go_next_pipe(mini));
	go_next_pipe(mini);
	if (command.infile != -2)
		close(command.infile);
	if (command.outfile != -2)
		close(command.outfile);
}

void	ft_denied(t_command cmd, t_minishell mini)
{
	error_msg("minishell: ");
	error_msg(cmd.cmd);
	error_msg(": Permission denied\n");
	quit(cmd, mini, 126);
}
