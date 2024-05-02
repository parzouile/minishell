/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:08:39 by aschmitt          #+#    #+#             */
/*   Updated: 2024/05/02 17:28:00 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_pwd(t_minishell mini)
{
	char	*tmp;
	char	*pwd;

	mini->env = remove_from_env(mini->env, "OLDPWD");
	tmp = get_value_cd(mini->env, "PWD");
	if (!tmp)
		return (0);
	pwd = ft_strjoin("OLDPWD=", tmp);
	if (!pwd)
		return (free(tmp), 0);
	add_value(&(mini->env), pwd);
	free(pwd);
	free(tmp);
	mini->env = remove_from_env(mini->env, "PWD");
	tmp = getcwd(NULL, 0);
	pwd = ft_strjoin("PWD=", tmp);
	if (!pwd)
		return (free(tmp), 0);
	free(tmp);
	add_value(&(mini->env), pwd);
	return (0);
}

int	cd_home(t_minishell mini)
{
	char	*s;

	s = get_value_cd(mini->env, "HOME");
	if (s == NULL)
	{
		g_current_status = 1;
		return (error_msg("minishell: cd: HOME not set\n"), 1);
	}
	if (chdir(s) != 0)
	{
		g_current_status = 1;
		perror("minishell: cd");
		free(s);
		return (1);
	}
	free(s);
	change_pwd(mini);
	return (0);
}

int	builtin_cd(char *s, t_minishell mini)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (error_cd(), 1);
	free(pwd);
	if (chdir(s) != 0)
	{
		g_current_status = 1;
		return (perror("minishell: cd"), 1);
	}
	change_pwd(mini);
	return (0);
}

int	cd_old(t_minishell mini)
{
	char	*s;

	s = get_value_cd(mini->env, "OLDPWD");
	if (s == NULL)
	{
		g_current_status = 1;
		return (error_msg("minishell: cd: OLDPWD not set\n"), 1);
	}
	if (builtin_cd(s, mini) == 1)
		return (free(s), 1);
	printf("%s\n", s);
	free(s);
	return (0);
}

int	ft_cd(t_command command, t_minishell mini)
{
	if (!command.args[1])
		return (cd_home(mini));
	if (command.args[2])
	{
		g_current_status = 1;
		return (write(2, "minishell: cd: too many arguments\n", 35), 1);
	}
	if (ft_strcmp(command.args[1], "~/") == 0
		|| ft_strcmp(command.args[1], "~") == 0)
		return (cd_home(mini));
	if (ft_strcmp(command.args[1], "-") == 0)
		return (cd_old(mini));
	builtin_cd(command.args[1], mini);
	return (0);
}
