/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:38:53 by jules             #+#    #+#             */
/*   Updated: 2024/04/27 00:57:43 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	double_chevrons(char *str)
{
	if ((str[0] == '<') && (str[1] == '<'))
		return (1);
	if ((str[0] == '>') && (str[1] == '>'))
		return (1);
	return (0);
}

int	next_special_char(char *str)
{
	int					i;
	char				quotes_char;
	int					in_quotes;
	static const char	*special_chars = " \t\n|<>";

	i = -1;
	in_quotes = 0;
	while (str[++i])
	{
		if (((str[i] == '"') || (str[i] == '\'')) && !in_quotes)
		{
			quotes_char = str[i];
			in_quotes = 1;
		}
		else if (in_quotes && (str[i] == quotes_char))
			in_quotes = 0;
		else if (!in_quotes && (ft_strchr(special_chars, str[i]) != NULL))
			break ;
	}
	return (i);
}

int	skip_spaces(char *str)
{
	int					i;
	static const char	*white_sp = " \t\n";

	i = -1;
	while (str[++i])
	{
		if (!ft_strchr(white_sp, str[i]))
			break ;
	}
	return (i);
}

int	tokenize(t_token *tok, char *str)
{
	int		i;
	int		tmp;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		i += skip_spaces(str + i);
		tmp = next_special_char(str + i);
		if (tmp == 0)
			tmp = 1 + double_chevrons(str + i);
		if (!str[i])
			break ;
		if (push_back(tok, new_token(ft_substr(str, i, tmp))))
			return (1);
		i += tmp;
	}
	return (0);
}
/**
 * a droite d'une redirection
 *  : ARG
 *  
*/
void	put_cmd_types(t_token tok)
{
	(void) tok;
	return ;
}