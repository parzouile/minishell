/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanacze <jbanacze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:30:45 by jbanacze          #+#    #+#             */
/*   Updated: 2024/05/02 15:51:12 by jbanacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

long long	ft_atoll(char *s, int *err_code)
{
	size_t				i;
	int					sign;
	unsigned long long	n;

	n = 0;
	sign = 1;
	i = 0;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	if ((s[i] < '0') || ('9' < s[i]))
		*err_code = 1;
	while (s[i] && (('0' <= s[i]) && (s[i] <= '9')))
	{
		n = n * 10 + (s[i] - '0');
		if (n > ((unsigned long long) LONG_MAX + 1 * (sign == -1)))
			break ;
		i++;
	}
	if (s[i])
		*err_code = 1;
	return (n * sign);
}

void	quit(t_command cmd, t_minishell mini, int n)
{
	end_command(cmd);
	free_minishell(mini);
	exit(n);
}

void	ft_exit(t_command cmd, t_minishell mini)
{
	int	err_code;
	int	n;

	printf("exit\n");
	err_code = 0;
	if (!cmd.args[1])
		quit(cmd, mini, g_current_status);
	n = ft_atoll(cmd.args[1], &err_code);
	if (err_code)
	{
		error_msg("minishell: exit: ");
		error_msg(cmd.args[1]);
		error_msg(": numeric argument required\n");
		quit(cmd, mini, 2);
	}
	if (cmd.args[2])
	{
		error_msg("minishell: exit: too many arguments\n");
		g_current_status = 1;
		return ;
	}
	quit(cmd, mini, n);
}
