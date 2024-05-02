/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanacze <jbanacze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 00:59:49 by aschmitt          #+#    #+#             */
/*   Updated: 2024/05/02 18:06:30 by jbanacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	go_next_pipe(t_minishell mini)
{
	while (mini->cmd_line && mini->cmd_line->type != 7)
	{
		if (!mini->cmd_line->next)
			break ;
		mini->cmd_line = mini->cmd_line->next;
	}
	if (mini->cmd_line && mini->cmd_line->type == 7)
		mini->cmd_line = mini->cmd_line->next;
}

pid_t	first_command(t_minishell mini, int pipefd[2])
{
	t_command	command;

	g_current_status = 0;
	command.exec = 0;
	if (nb_command(mini->cmd_line) == 0)
	{
		return (zero_command(mini), 0);
	}
	command.args = take_args(&mini->cmd_line, &command);
	if (command.args == NULL)
		return (go_next_pipe(mini), 0);
	if (redirection(&command, &mini->cmd_line, mini) == 0 || command.exec)
		return (go_next_pipe(mini), close(pipefd[1]), end_command(command), 1);
	if (command.outfile == -2)
		command.outfile = pipefd[1];
	else
		close(pipefd[1]);
	while (mini->cmd_line && mini->cmd_line->type != 7)
		mini->cmd_line = mini->cmd_line->next;
	mini->cmd_line = mini->cmd_line->next;
	return (ft_exec(mini, command, pipefd));
}

int	args_and_file(t_command *command, t_minishell mini, int p[2], int n[2])
{
	command->args = take_args(&mini->cmd_line, command);
	if (command->args == NULL)
		return (go_next_pipe(mini), 0);
	if (redirection(command, &mini->cmd_line, mini) == 0 || command->exec)
		return (go_next_pipe(mini), end_command(*command), 0);
	if (command->infile == -2)
		command->infile = p[0];
	else
		close(p[0]);
	if (command->outfile == -2)
		command->outfile = n[1];
	return (1);
}

pid_t	mid_command(t_minishell mini, int pipefd[2])
{
	t_command	command;
	int			newpipe[2];
	pid_t		pid;

	close(pipefd[1]);
	command.exec = 0;
	if (g_current_status == 130)
		return (close(pipefd[0]), 0);
	if (pipe(newpipe) == -1)
		return (close(pipefd[0]), 0);
	if (nb_command(mini->cmd_line) == 0)
	{
		close(pipefd[0]);
		pipefd[0] = newpipe[0];
		pipefd[1] = newpipe[1];
		return (zero_command(mini), 0);
	}
	if (args_and_file(&command, mini, pipefd, newpipe) == 0)
		return (0);
	go_next_pipe(mini);
	pid = ft_exec3(mini, command);
	pipefd[0] = newpipe[0];
	pipefd[1] = newpipe[1];
	return (pid);
}

pid_t	last_command(t_minishell mini, int pipefd[2])
{
	t_command	cmd;

	close(pipefd[1]);
	cmd.exec = 0;
	if (g_current_status == 130)
		return (close(pipefd[0]), 0);
	if (nb_command(mini->cmd_line) == 0)
	{
		close(pipefd[0]);
		return (zero_command(mini), 0);
	}
	cmd.args = take_args(&mini->cmd_line, &cmd);
	if (cmd.args == NULL)
		return (0);
	if (redirection(&cmd, &mini->cmd_line, mini) == 0 || cmd.exec)
		return (end_command(cmd), 0);
	if (cmd.infile == -2)
		cmd.infile = pipefd[0];
	else
		close(pipefd[0]);
	if (cmd.outfile == -2)
		cmd.outfile = 1;
	return (ft_exec3(mini, cmd));
}
