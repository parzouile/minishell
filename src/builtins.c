/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:08:54 by aschmitt          #+#    #+#             */
/*   Updated: 2024/04/24 13:38:18 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_cd(t_command command)
{
	if (command.args[2])
		return (write(2, "minishell: cd: too many arguments\n", 35), 1);
	// changer pwd et old
	
}

int	builtin(t_minishell mini, int pipefd[2], char **envp)
{
	t_command	command;

	
	command.cmd = mini->cmd_line->str;
	command.args = take_args(&mini->cmd_line);
	command.infile = -2;
	command.outfile = -2;
	if (find_file(&command,  &mini->cmd_line) == 1)
		return (free(command.args), 1);
	if (ft_strcmp(command.cmd, "cd") == 0)
		return (ft_cd(command));
	else if (ft_strcmp(command.cmd, "exit") == 0)
	
		return (ft_exit(command, wstatus), 0); // fix pas atoi mais unsigned char ou char 
	else if (ft_strcmp(command.cmd, "export") == 0)
	
		return (ft_export(command, m_envp, wstatus), 0);
	else if (ft_strcmp(command.cmd, "unset") == 0)
	
		return (ft_unset(command, m_envp), 0);
	return (1);
}
