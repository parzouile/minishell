/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:14:03 by aschmitt          #+#    #+#             */
/*   Updated: 2024/04/30 10:16:28 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_pwd(t_minishell mini)
{
	char	buffer[2048];
	char	*tmp;

	getcwd(buffer, 2048);
	mini->env = remove_from_env(mini->env, "OLDPWD");
	tmp = ft_strjoin("OLDPWD=", get_value(mini->env, "PWD"));
	if (!tmp)
		return ;
	add_value(&(mini->env), tmp);
	free(tmp);
	mini->env = remove_from_env(mini->env, "PWD");
	getcwd(buffer, 2048);
	tmp = ft_strjoin("PWD=", buffer);
	if (!tmp)
		return ;
	add_value(&(mini->env), tmp);
	free(tmp);
}

int	ft_cd(t_command command, t_minishell mini)
{
	if (!command.args[1])
	{
		command.args[1] = get_value(mini->env, "HOME");
		if (chdir(command.args[1]) != 0)
			perror("minishell: cd");
		else
			free(command.args[1]);
	}
	else if (command.args[2])
		return (write(2, "minishell: cd: too many arguments\n", 35), 1);
	else
	{
		if (chdir(command.args[1]) != 0)
			perror("minishell: cd");
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
