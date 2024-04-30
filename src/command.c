/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 00:59:49 by aschmitt          #+#    #+#             */
/*   Updated: 2024/04/30 17:41:54 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	ft_exec(t_minishell mini, t_command command, int pipefd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (0); // error
	else if (pid == 0)
	{
		dup2(command.outfile, STDOUT_FILENO);
		if (command.infile)
			dup2(command.infile, STDIN_FILENO);
		close(pipefd[0]);
		if (builtin(mini, command, mini->envp) == 1)
		{
			execve(command.cmd, command.args, mini->envp);
			perror("minishell");
			// error_msg("minishell: command not found\n");
		}
		exit(0);
	}
	end_command(command);
	return (pid);
}

pid_t	ft_exec3(t_minishell mini, t_command command)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (0); // error
	else if (pid == 0)
	{
		dup2(command.outfile, STDOUT_FILENO);
		dup2(command.infile, STDIN_FILENO);
		if (builtin(mini, command, mini->envp) == 1)
		{
			execve(command.cmd, command.args, mini->envp);
			perror("minishell");
			// error_msg("minishell: command not found\n");
		}
		exit(0);
	}
	end_command(command);
	return (pid);
}

pid_t	first_command(t_minishell mini, int pipefd[2])
{
	t_command	command;

	command.args = take_args(&mini->cmd_line, &command);
	if (command.args == NULL)
		return (0);
	if (redirection(&command, &mini->cmd_line) == 0)
		return (0);// fermer fd et free
	if (command.outfile == -2)
		command.outfile = pipefd[1];
	else
		close(pipefd[1]);
	while (mini->cmd_line && mini->cmd_line->type != 7)
		mini->cmd_line = mini->cmd_line->next;
	mini->cmd_line = mini->cmd_line->next;
	return (ft_exec(mini, command, pipefd));
}

pid_t	mid_command(t_minishell mini, int pipefd[2])
{
	t_command	command;
	int			newpipe[2];
	pid_t		pid;

	close(pipefd[1]);
	if (pipe(newpipe) == -1)
		return (close(pipefd[0]), 1);
	command.args = take_args(&mini->cmd_line, &command);
	if (command.args == NULL)
		return (0);
	if (redirection(&command, &mini->cmd_line) == 0)
		return (0); // fermer fd et free
	if (command.infile == -2)
		command.infile = pipefd[0];
	else
		close(pipefd[0]);
	if (command.outfile == -2)
		command.outfile = newpipe[1];
	while (mini->cmd_line && mini->cmd_line->type != 7)
		mini->cmd_line = mini->cmd_line->next;
	mini->cmd_line = mini->cmd_line->next;
	pid = ft_exec3(mini, command);
	pipefd[0] = newpipe[0];
	pipefd[1] = newpipe[1];
	return (pid);
}

pid_t	last_command(t_minishell mini, int pipefd[2])
{
	t_command	command;

	close(pipefd[1]);
	command.args = take_args(&mini->cmd_line, &command);
	if (command.args == NULL)
		return (0);
	if (redirection(&command, &mini->cmd_line) == 0)
		return (0); // fermer fd et free
	if (command.infile == -2)
		command.infile = pipefd[0];
	else
		close(pipefd[0]);
	if (command.outfile == -2)
		command.outfile = 1;
	return (ft_exec3(mini, command));
}
