/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:01:14 by aschmitt          #+#    #+#             */
/*   Updated: 2024/04/27 18:41:31 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	commande(t_command cmd, int pipefd[2], char **envp)
{
	pid_t	pid;
	int	new_pipe[2];

	close(pipefd[1]);
	if (pipe(new_pipe) == -1)
		return (close(pipefd[0]), 1);
	pid = fork();
	if (pid == -1)
	{
		if (cmd.infile != -2)
			close(cmd.infile);
		if (cmd.outfile != -2)
			close(cmd.outfile);
		close(pipefd[0]);
		close(new_pipe[0]);
		close(new_pipe[1]);
		return (1);
	}
	else if (pid == 0)
	{
		if (cmd.cmd[0] != '/' && cmd.cmd[0] != '.')
			cmd.cmd = find_bin(cmd.cmd, envp);
		execve(cmd.cmd, cmd.args, envp);
		// close(pipefd[0]);
		// command(cmd, envp);
	}
	pipefd[0] = new_pipe[0];
	pipefd[1] = new_pipe[1];
	return (0);
}

// void	start_command(t_minishell mini, int pipefd[2])
// {	
// 	t_command	command;
// 	char		**envp;

// 	envp = tenv_to_arr(mini->env);
// 	if (!envp)
// 		return ;
// 	command.cmd = mini->cmd_line->str;
// 	command.infile = -2;
// 	command.outfile = -2;
// 	command.args = take_args(&mini->cmd_line);
// 	if (redirection(&command,  &mini->cmd_line) == 0)
// 		return ; // fermer fd et free avancer mini.cmd_line
// 	if (mini->cmd_line == NULL && command.outfile == -2)
// 		command.outfile = 1;
// 	else if (mini->cmd_line && mini->cmd_line->type == 7)
// 		mini->cmd_line = mini->cmd_line->next;
// 	if (builtin(mini, command, pipefd, envp) == 1)
// 		commande(command, pipefd, envp);
// 	end_command(command, envp);
// }
