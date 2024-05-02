/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_2_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:07:05 by aschmitt          #+#    #+#             */
/*   Updated: 2024/05/02 16:10:31 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
