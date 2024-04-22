/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:38:53 by jules             #+#    #+#             */
/*   Updated: 2024/04/23 00:40:10 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_type(char *str)
{
	if (!ft_strcmp(str, "|"))
		return (PIPE);
	if (!ft_strcmp(str, "<"))
		return (INFILE);
	if (!ft_strcmp(str, "<<"))
		return (INFILE_HEREDOC);
	if (!ft_strcmp(str, ">"))
		return (OUTFILE);
	if (!ft_strcmp(str, ">>"))
		return (OUTFILE_APPEND);
	return (ARG);
}

t_token	new_token(char *str)
{
	t_token	tok;

	if (!str)
		return (NULL);
	tok = malloc(sizeof(struct s_token));
	if (!tok)
		return (NULL);
	tok->next = NULL;
	tok->prev = NULL;
	tok->str = str;
	tok->type = get_type(str);
	return (tok);
}

void	free_token(t_token tok)
{
	if (!tok)
		return ;
	free(tok->str);
	free(tok);
}

void	free_tokens(t_token tok)
{
	if (!tok)
		return ;
	free_tokens(tok->next);
	free_token(tok);
}

int	push_back(t_token *tok, t_token new)
{
	int	return_value;

	if (!tok || !new)
		return (1);
	if (!(*tok))
	{
		*tok = new;
		return (0);
	}
	return_value = push_back(&((*tok)->next), new);
	if ((*tok)->next)
		(*tok)->next->prev = *tok;
	return (return_value);
}

int	double_chevron(char *str)
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
		if (in_quotes && (str[i] == quotes_char))
			in_quotes = 0;
		if (in_quotes)
			continue ;
		if (ft_strchr(special_chars, str[i]) != NULL)
		{
			//i += double_chevron(str + i);
			break ;
		}
	}
	return (i);
}

int	skip_spaces(char *str)
{
	int					i;
	static const char	*white_sp =" \t\n";

	i = -1;
	while (str[++i])
	{
		if (!ft_strchr(white_sp, str[i]))
			break;
	}
	return (i);
}

int	tokenize(t_token *tok, char *str)
{
	int		i;
	int		tmp;

	i = 0;
	while(str[i])
	{
		i += skip_spaces(str + i);
		tmp = next_special_char(str + i);
		if (!str[i])
			break ;
		if (push_back(tok, new_token(ft_substr(str, i, tmp + (tmp == 0)))))
			return (1);
		i += tmp + (tmp == 0);
	}
	return (0);
}
