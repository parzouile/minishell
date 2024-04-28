/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 00:59:49 by aschmitt          #+#    #+#             */
/*   Updated: 2024/04/28 01:45:28 by aschmitt         ###   ########.fr       */
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
	// if (cmd.infile)
	// 	close(cmd.infile);
	// if (cmd.outfile && cmd.outfile != 1)
	// 	close(cmd.outfile);
}

void	ft_exec(t_minishell mini, t_command command, char **envp, int pipefd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return ;// error
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
}

void	first_command(t_minishell mini, int pipefd[2])
{
	t_command	command;
	char		**envp;

	envp = tenv_to_arr(mini->env); // a double free
	if (!envp)
		return ;
	command.args = take_args(&mini->cmd_line, &command);
	if (redirection(&command,  &mini->cmd_line) == 0)
		return ; // fermer fd et free
	if (command.outfile == -2)
		command.outfile = pipefd[1];
	else
		close(pipefd[1]);
	if (mini->cmd_line && mini->cmd_line->type == 7)
		mini->cmd_line = mini->cmd_line->next;
	ft_exec(mini, command, envp, pipefd);
	command_end(command, envp);
}

void	ft_exec3(t_minishell mini, t_command command, char **envp, int pipefd[2])
{
	pid_t	pid;

	close(pipefd[1]);
	pid = fork();
	if (pid == -1)
		return ;// error
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
}

void	last_command(t_minishell mini, int pipefd[2])
{
	t_command	command;
	char		**envp;

	envp = tenv_to_arr(mini->env); // a double free
	if (!envp)
		return ;
	command.args = take_args(&mini->cmd_line, &command);
	if (redirection(&command,  &mini->cmd_line) == 0)
		return ; // fermer fd et free
	if (command.infile == -2)
		command.infile = pipefd[0];
	else
		close(pipefd[0]);
	if (command.outfile == -2)
		command.outfile = 1;
	// verifie NULL 
	ft_exec3(mini, command, envp, pipefd);
	command_end(command, envp);
	return ;
}