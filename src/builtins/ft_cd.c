/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:08:39 by aschmitt          #+#    #+#             */
/*   Updated: 2024/05/02 16:10:24 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_pwd(t_minishell mini)
{
	char	buffer[2048];
	char	*tmp;
	char	*s;

	getcwd(buffer, 2048);
	mini->env = remove_from_env(mini->env, "OLDPWD");
	s = get_value(mini->env, "PWD");
	tmp = ft_strjoin("OLDPWD=", s);
	if (!tmp)
		return ;
	if (s)
		free(s);
	add_value(&(mini->env), tmp);
	if (tmp)
		free(tmp);
	mini->env = remove_from_env(mini->env, "PWD");
	getcwd(buffer, 2048);
	tmp = ft_strjoin("PWD=", buffer);
	if (!tmp)
		return ;
	add_value(&(mini->env), tmp);
	free(tmp);
}

char	*get_value_cd(t_env env, char *key)
{
	if (!key)
	{
		return (NULL);
	}
	if (!env)
	{
		return (NULL);
	}
	if (ft_strcmp(env->name, key) == 0)
	{
		return (ft_strdup(env->value));
	}
	return (get_value_cd(env->next, key));
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
		if (s)
			free(s);
		return (1);
	}
	free(s);
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
	if (chdir(s) != 0)
	{
		g_current_status = 1;
		perror("minishell: cd");
		if (s)
			free(s);
		return (1);
	}
	printf("%s\n", s);
	free(s);
	change_pwd(mini);
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
	else if (chdir(command.args[1]) != 0)
	{
		g_current_status = 1;
		return (perror("minishell: cd"), 1);
	}
	change_pwd(mini);
	return (0);
}
