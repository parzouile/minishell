/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanacze <jbanacze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:56:08 by jules             #+#    #+#             */
/*   Updated: 2024/04/30 10:11:37 by jbanacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_char(char c)
{
	return ((c == '_') || ft_isalnum(c));
}

int	next_dollar_sign(char *str, int *in_dquotes)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !(*in_dquotes))
		{
			i++;
			while (str[i] && (str[i] != '\''))
				i++;
		}
		if (str[i] == '\"')
			*in_dquotes = !(*in_dquotes);
		if (str[i] == '$')
			break ;
		i++;
	}
	return (i);
}

int	lst_full_length(t_list *lst)
{
	if (!lst)
		return (0);
	return (ft_strlen(lst->content) + lst_full_length(lst->next));
}

char	*lst_to_str(t_list *lst)
{
	int		fl;
	char	*res;
	int		i;
	int		j;

	fl = lst_full_length(lst);
	res = malloc(sizeof(char) * (fl + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (lst)
	{
		j = -1;
		while (((char *)lst->content)[++j])
			res[i++] = ((char *)lst->content)[j];
		lst = lst->next;
	}
	res[i] = 0;
	return (res);
}

void	treat_quote_expanded(char *s, int restore)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!restore && ((s[i] == '\'') || (s[i] == '"')))
		{
			s[i] = -s[i];
		}
		if (restore && (s[i] < 0))
		{
			s[i] = -s[i];
		}
		i++;
	}
}