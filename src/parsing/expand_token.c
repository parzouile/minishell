/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanacze <jbanacze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:00:38 by jbanacze          #+#    #+#             */
/*   Updated: 2024/04/24 16:05:49 by jbanacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_char(char c)
{
	return (1);
}

int	value_length(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		
		i++;
	}
	return (i);
}

int	expand_token(t_token tok,)
{
	char	*new_str;
	char	*tmp_str;
	char	*var_name;
	int		i;
}
