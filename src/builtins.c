/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:33:10 by aschmitt          #+#    #+#             */
/*   Updated: 2024/04/30 13:40:40 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_bultins(t_minishell mini, char **envp, t_command command)
{
	if (ft_strcmp(command.cmd, "cd") == 0)
		ft_cd(command, mini);
	else if (ft_strcmp(command.cmd, "echo") == 0)
		ft_echo(command);
	else if (ft_strcmp(command.cmd, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(command.cmd, "env") == 0)
		ft_envp(envp);
}

int	builtin_null(t_command command)
{
	if (ft_strcmp(command.cmd, "export") == 0)
		return (0);
	else if (ft_strcmp(command.cmd, "exit") == 0)
		return (0);
	else if (ft_strcmp(command.cmd, "unset") == 0)
		return (0);
	return (1);
}

int	is_builtin(char *s)
{
	if (ft_strcmp(s, "cd") == 0)
		return (1);
	else if (ft_strcmp(s, "echo") == 0)
		return (1);
	else if (ft_strcmp(s, "pwd") == 0)
		return (1);
	else if (ft_strcmp(s, "env") == 0)
		return (1);
	else if (ft_strcmp(s, "export") == 0)
		return (1);
	else if (ft_strcmp(s, "exit") == 0)
		return (1);
	else if (ft_strcmp(s, "unset") == 0)
		return (1);
	return (0);
}

int	builtin(t_minishell mini, t_command command, char **envp)
{
	if (builtin_null(command) == 0)
		return (0);
	if (!is_builtin(command.cmd))
		return (1);
	find_bultins(mini, envp, command);
	return (0);
}

int	one_builtin(t_minishell mini, t_command command, char **envp)
{
	if (ft_strcmp(command.cmd, "echo") == 0)
		return (ft_echo(command), 0);
	else if (ft_strcmp(command.cmd, "cd") == 0)
		return (ft_cd(command, mini), 0);
	else if (ft_strcmp(command.cmd, "pwd") == 0)
		return (ft_pwd(), 0);
	else if (ft_strcmp(command.cmd, "env") == 0)
		return (ft_envp(envp), 0);
	else if (ft_strcmp(command.cmd, "exit") == 0)
		return (mini->exit = 0, 0);
	else if (ft_strcmp(command.cmd, "unset") == 0)
		return (ft_unset(mini, command), 0);
	else if (ft_strcmp(command.cmd, "export") == 0)
		return (ft_export(mini, command), 0);
	return (1);
}
