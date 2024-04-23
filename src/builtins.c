/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:08:54 by aschmitt          #+#    #+#             */
/*   Updated: 2024/04/23 14:33:07 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_cd()
{
    
}

void    builtin(t_command cmd, int pipefd[2], char **envp)
{
    if(ft_strcmp(command->cmd, "cd") == 0)
		return(ft_cd(command, wstatus), 0);
	else if (ft_strcmp(command->cmd, "exit") == 0)
		return (ft_exit(command, wstatus), 0); // fix pas atoi mais unsigned char ou char 
	else if (ft_strcmp(command->cmd, "export") == 0)
		return (ft_export(command, m_envp, wstatus), 0);
	else if (ft_strcmp(command->cmd, "unset") == 0)
		return (ft_unset(command, m_envp), 0);
	return (1);
}