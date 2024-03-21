/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:01:21 by aschmitt          #+#    #+#             */
/*   Updated: 2024/03/21 11:12:31 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*skip_space(char *s)
{
	int		i;
	int		a;
	int		j;
	char	*str;

	i = 0;
	while (s[i] && (s[i] == ' ' || (s[i] >= 7 && s[i] <= 13)))
		i++;
	a = i;
	while (s[a])
		a++;
	a--;
	while (a > i && (s[a] == ' ' || (s[a] >= 7 && s[a] <= 13)))
		a--;
	j = -1;
	str = (char *)(malloc(sizeof(char) * (a - i + 2)));
	if (!str)
		return (NULL);
	while (i <= a)
		str[++j] = s[i++];
	str[++j] = 0;
	free(s);
	return (str);
}

/*int	is_token(char c)
{
	return	(c == '|' || c == ';' || c == '&' || c == '>' || c == '<');
}

int	count_token(char *s)
{
	int		i;
	int		a;
	int		count;
	char	c;

	i = -1;
	count = 0;
	while (s[++i])
	{
		a = i;
		while(s[i] && !is_token(s[i]))
		{
			c = s[i];
			if (c == '\'' || c == '\"')
			{
				i++;
				while (s[i] && s[i] != c)
					i++;
			}
			i++;
		}
		if ((s[i] == '>' && s[i + 1] == '>') || 
			(s[i] == '<' && s[i + 1] == '<') || (s[i] == '&' && s[i + 1] == '&'))
			i++;
		if (a != i || i == 0)
			count++;
		printf("a = %c i = %c\n", s[a], s[i]);
		if (!s[i])
			return (count);
		count++;
	}
	return (count);
}

char	**split_token(char *s)
{
	int	size;

	size = count_token(s);
	printf("size = %d\n", size);
	return (NULL);
}*/

int	verif_line(char *s)
{
	int		i;
	int		p;
	char	c;

	p = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == '(')
			p++;
		if (s[i] == ')')
			p--;
		if (s[i] == '\'' || s[i] == '\"')
		{
			c = s[i];
			i++;
			while (s[i] && s[i] != c)
				i++;
			if (!s[i])
				return (0);
		}
	}
	return (p == 0);
}

int	check_pipe(char *s)
{
	int	i;

	i = 1;
	while (s[i - 1] && s[i])
	{
		if (s[i - 1] == '|' && s[i] == '|')
		{
			printf("Error syntax error |\n");
			return (1);
		}
		i++;
	}
	return (0);
}

void	before_pipe(char *s)
{
	char	**lst_pipe;
	int		i;

	if (check_pipe(s))
		return ;
	lst_pipe = ft_split(s, '|');
	i = -1;
	while (lst_pipe[++i])
	{
		lst_pipe[i] = skip_space(lst_pipe[i]);
		printf("%d : %s\n", i, lst_pipe[i]);
		free(lst_pipe[i]);
	}
	free(lst_pipe);
}

void	parsing(char **s)
{
	char	**lst;
	int		i;

	*s = skip_space(*s);
	if (!*s || ft_strncmp("exit", *s, 5) == 0)
		ft_exit();
	if (verif_line(*s) == 0)
	{
		printf("Error missing \" or \' or )\n");
		return ;
	}
	lst = ft_split(*s, ';');
	i = -1;
	while (lst[++i])
	{
		printf("%d before pipe\n", i);
		before_pipe(lst[i]);
		free(lst[i]);
	}
	free(lst);
	printf("%s\n", *s);
}
