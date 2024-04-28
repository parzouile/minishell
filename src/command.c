/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 00:59:49 by aschmitt          #+#    #+#             */
/*   Updated: 2024/04/28 18:24:10 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_end(t_command cmd, char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		free(envp[i]);
	free(envp);
	free(cmd.args);
	close(cmd.infile);
	close(cmd.outfile);
}

pid_t	ft_exec(t_minishell mini, t_command command, char **envp, int pipefd[2])
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
		if (builtin(mini, command, envp) == 1) // pas sur p-e modifie  envp ???
		{
			if (command.cmd[0] != '/' && command.cmd[0] != '.')
				command.cmd = find_bin(command.cmd, envp); // free this later
			execve(command.cmd, command.args, envp);
			error_msg("minishell: command not found\n");	
		}
		exit(0);
	}
	command_end(command, envp);
	return (pid);
}

pid_t	first_command(t_minishell mini, int pipefd[2])
{
	t_command	command;
	char		**envp;

	envp = tenv_to_arr(mini->env); // a double free
	if (!envp)
		return (0);
	command.args = take_args(&mini->cmd_line, &command);
	if (redirection(&command,  &mini->cmd_line) == 0)
		return (0);// fermer fd et free
	if (command.outfile == -2)
		command.outfile = pipefd[1];
	else
		close(pipefd[1]);
	if (mini->cmd_line && mini->cmd_line->type == 7)
		mini->cmd_line = mini->cmd_line->next;
	return (ft_exec(mini, command, envp, pipefd));
}

pid_t	ft_exec3(t_minishell mini, t_command command, char **envp, int pipefd[2])
{
	pid_t	pid;

	close(pipefd[1]);
	pid = fork();
	if (pid == -1)
		return (0);// error
	else if (pid == 0)
	{
		dup2(command.outfile, STDOUT_FILENO);
		dup2(command.infile, STDIN_FILENO);
		if (builtin(mini, command, envp) == 1) // pas sur p-e modifie  envp ???
		{
			if (command.cmd[0] != '/' && command.cmd[0] != '.')
				command.cmd = find_bin(command.cmd, envp); // free this later
			execve(command.cmd, command.args, envp);
			error_msg("minishell: command not found\n");	
		}
		exit(0);
	}
	close(pipefd[0]);
	command_end(command, envp);
	return (pid);
}

pid_t	last_command(t_minishell mini, int pipefd[2])
{
	t_command	command;
	char		**envp;

	envp = tenv_to_arr(mini->env); // a double free
	if (!envp)
		return (0);
	command.args = take_args(&mini->cmd_line, &command);
	if (redirection(&command,  &mini->cmd_line) == 0)
		return (0); // fermer fd et free
	
	if (command.infile == -2)
		command.infile = pipefd[0];
	else
		close(pipefd[0]);
	if (command.outfile == -2)
		command.outfile = 1;
	// verifie NULL 
	return (ft_exec3(mini, command, envp, pipefd));
}

pid_t	ft_exec2(t_minishell mini, t_command cmd, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (0);// error
	else if (pid == 0)
	{
		dup2(cmd.infile, STDIN_FILENO);
		dup2(cmd.outfile, STDOUT_FILENO);
		if (builtin(mini, cmd, envp) == 1) // pas sur p-e modifie  envp ???
		{
			if (cmd.cmd[0] != '/' && cmd.cmd[0] != '.')
				cmd.cmd = find_bin(cmd.cmd, envp);
			execve(cmd.cmd, cmd.args, envp);
			error_msg("minishell: command not found\n");
		}
		exit(0);
	}
	return (pid);
}

pid_t	mid_command(t_minishell mini, int pipefd[2])
{
	t_command	command;
	char		**envp;
	int		newpipe[2];
	pid_t		pid;
	
	close(pipefd[1]);
	envp = tenv_to_arr(mini->env); // a double free
	if (!envp)
		return (0);
	if (pipe(newpipe) == -1)
		return (close(pipefd[0]), 1);
	command.args = take_args(&mini->cmd_line, &command);
	if (redirection(&command,  &mini->cmd_line) == 0)
		return (0); // fermer fd et free
	if (command.infile == -2)
		command.infile = pipefd[0];
	else
		close(pipefd[0]);
	if (command.outfile == -2)
		command.outfile = newpipe[1];
	else
		close(newpipe[1]);
	if (mini->cmd_line && mini->cmd_line->type == 7)
		mini->cmd_line = mini->cmd_line->next;
	pid = ft_exec2(mini, command, envp);
	command_end(command, envp);
	pipefd[0] = newpipe[0];
	pipefd[1] = newpipe[1];
	return (pid);
}
