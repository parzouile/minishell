/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanacze <jbanacze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:00:38 by jbanacze          #+#    #+#             */
/*   Updated: 2024/04/26 07:35:48 by jbanacze         ###   ########.fr       */
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
			break;
		i++;
	}
	return (i);
}

int	value_length(char *str, int in_dquotes)
{
	int	i;

	if (!is_valid_char(str[1]))
		return (in_dquotes - 1);
	if (ft_isdigit(str[1]))
		return (2);
    i = 1;
	while (str[i] && is_valid_char(str[i]))
		i++;
	return (i);
}

char	*get_expanded_value(t_minishell mini, char *str, int len_var)
{
	char	*var_name;
	char	*value;

	if (len_var == -1)
		return (ft_calloc(1, sizeof(char)));
	if (len_var == 0)
	{
		value = ft_calloc(2, sizeof(char));
		if (!value)
			return (NULL);
		value[0] = '$';
		return (value);
	}
	var_name = ft_substr(str, 1, len_var - 1);
	value = get_value(mini->env, var_name);
	if (var_name)
		free(var_name);
	if (!value)
		return (NULL);
	return (value);
}

int	lst_full_length(t_list *lst)
{
	if (!lst)
		return (0);
	return (ft_strlen(lst->content) + lst_full_length(lst->next));
}

char *lst_to_str(t_list *lst)
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

char	*expand_str(t_minishell mini, char *str)
{
	t_list	*expanded_lst;
	char	*expanded_str;
	int		in_dquotes;
	int		next;
	int		len_var;

	expanded_lst = NULL;
	in_dquotes = 0;
	while (*str)
	{
		next = next_dollar_sign(str, &in_dquotes);
		len_var = 0;
		if (next)
			ft_lstadd_back(&expanded_lst, ft_lstnew(ft_substr(str, 0, next)));
		else
		{
			len_var = value_length(str, in_dquotes);
			ft_lstadd_back(&expanded_lst, \
				ft_lstnew(get_expanded_value(mini, str, len_var)));
		}
		str = str + next + (len_var > 0) * len_var + \
			1 * (next == 0) * (len_var <= 0);
	}
	expanded_str = lst_to_str(expanded_lst);
	ft_lstclear(&expanded_lst, free);
	return (expanded_str);
}
