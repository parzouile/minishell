/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:14:03 by aschmitt          #+#    #+#             */
/*   Updated: 2024/05/02 14:19:29 by aschmitt         ###   ########.fr       */
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

void	ft_pwd(void)
{
	char	buffer[2048];

	getcwd(buffer, 2048);
	printf("%s\n", buffer);
}

void	ft_envp(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		printf("%s\n", envp[i]);
}

int	is_echon(char *s)
{
	int	i;

	i = 1;
	if (!s)
		return (0);
	if (s[0] == '-')
	{
		while (s[i] == 'n')
			i++;
		if (!s[i])
			return (1);
	}
	return (0);
}

void	ft_echo(t_command command)
{
	int	i;
	int	n;

	i = 1;
	while (is_echon(command.args[i]))
		i++;
	n = i == 1;
	if (command.args[i])
		printf("%s", command.args[i]);
	while (command.args[i] && command.args[++i])
	{
		printf(" %s", command.args[i]);
	}
	if (n)
		printf("\n");
}

void	ft_unset(t_minishell mini, t_command cmd)
{
	int	i;

	i = 0;
	while (cmd.args[++i])
		mini->env = remove_from_env(mini->env, cmd.args[i]);
}

void	ft_export(t_minishell mini, t_command cmd)
{
	int		i;
	int		j;
	char	*key;

	i = 0;
	while (cmd.args[++i])
	{
		j = is_valid_name(cmd.args[i]);
		if (!j)
		{
			g_current_status = 1;
			error_msg("minishell: export: '");
			error_msg(cmd.args[i]);
			error_msg("': not a valid identifier\n");
			continue ;
		}
		if (!cmd.args[i][j])
			continue ;
		key = ft_substr(cmd.args[i], 0, j);
		if (!key)
			continue ;
		mini->env = remove_from_env(mini->env, key);
		free(key);
		add_value(&(mini->env), cmd.args[i]);
	}
}
