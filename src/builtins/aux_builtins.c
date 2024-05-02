/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanacze <jbanacze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:14:03 by aschmitt          #+#    #+#             */
/*   Updated: 2024/05/02 16:26:03 by jbanacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cut_last_slash(char *str)
{
	int	i;
	int	index_last_slash;

	i = 0;
	index_last_slash = 0;
	if (!str)
		return ;
	while (str[i])
	{
		if (str[i] == '/')
			index_last_slash = i;
		i++;
	}
	str[index_last_slash + 1] = 0;
}

void	ft_envp(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		printf("%s\n", envp[i]);
}

void	ft_pwd(void)
{
	char	buffer[2048];

	getcwd(buffer, 2048);
	printf("%s\n", buffer);
}
